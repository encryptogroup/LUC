import sys
import re
import math

class Node:
        def __init__(self,inp,output,t,number):
                self.inp = inp
                self.output = output
                self.t = t
                self.number = number
        def shdl(self, outlabel, nodes):
                if(self.t == "input"):
                        return str(self.output[0])+ " input"
                if(self.t == "gate"):
                        fb = []
                        for bits in self.function_bits:
                                fb.append(' '.join( [ str(a) for a in bits] ))
                        outputlabel = ""
                        if outlabel:
                                for out in self.output:
                                        for n in nodes:
                                                if n.t == "output":
                                                        if out in n.inp:
                                                                outputlabel = " output"

                        return ' '.join([ str(a) for a in self.output]) + outputlabel +" gate arity "+str(len(self.inp)) + " table [ " + ' ] [ '.join(fb) + " ] inputs [ " + ' '.join([ str(a) for a in self.inp]) + " ]"
                return str(self.inp[0])


        def __lt__(self,other):
                return (self.t == "input" and other.t == "gate") or (self.t == "gate" and other.t == "output")  or (self.t == "input" and other.t == "output")
        def __repr__(self):
                return "[ " + ', '.join([ str(a) for a in self.inp]) + " ] " + "[ " + ', '.join([ str(a) for a in self.output]) + " ]"

# this is originally from
# https://stackoverflow.com/questions/312443/how-do-you-split-a-list-into-evenly-sized-chunks
def subdivide(lst,size):
        for i in range(0, len(lst),int(size)):
                yield lst[i:i+int(size)]

def remove_big_gates(nodes,max_fanout):
        new_nodes = []
        for node in nodes:
                if node.t != "gate":
                        new_nodes.append(node)
                elif node.t == "gate":
                        if len(node.output) <= max_fanout:
                                new_nodes.append(node)
                        else:
                                subdivided_outputs = list(subdivide(node.output,max_fanout))
                                subdivided_function_bits = list( subdivide(node.function_bits,max_fanout) )
                                for i in range(len(subdivided_outputs)):
                                        new_node = Node(node.inp,subdivided_outputs[i],node.t,0)
                                        new_node.function_bits = subdivided_function_bits[i]
                                        new_nodes.append(new_node)
        return new_nodes


change_in_pass = True

def process_file(inputfile, outputfile, max_fanout, outlabel):
        max_fanout = max(max_fanout,2)
        global change_in_pass
        f = open(inputfile,"r")
        original_nodes = []
        for line in f.readlines():
                elements = re.split(r'\s*[=,()\n\s]\s*', line)
                if(elements[1] == "input"):
                        original_nodes.append(Node([],[ int(elements[0]) ],"input",0))
                elif ("gate" in elements):
                        i = 0
                        outputs = []
                        while elements[i] != "gate":
                                outputs.append(int(elements[i]))
                                i = i + 1
                        arity = int(elements[i+2])
                        i = i + 5
                        function_bits = []
                        for j in range(len(outputs)):
                                fb = []
                                for k in range(2**arity):
                                        b = elements[i+j*(2**arity + 2) +k]
                                        fb.append(b)
                                function_bits.append(fb)
                        i = -3
                        inputs = []
                        while elements[i] != "[":
                                inputs.append(int(elements[i]))
                                i = i - 1
                        inputs.reverse()
                        newnode = Node(inputs,outputs,"gate",0)
                        newnode.function_bits = function_bits
                        original_nodes.append(newnode)

                elif "outputs" in elements:
                        del elements[0]
                        if(elements[-1] == ''):
                                del elements[-1]
                        #del elements[-1]
                        for e in elements:
                                original_nodes.append(Node([int(e)],[],"output",0))

        original_nodes = remove_big_gates(original_nodes,max_fanout)
        new_nodes = original_nodes
        while change_in_pass:
                new_nodes = reduce_fanout_pass(original_nodes,max_fanout)
                original_nodes = new_nodes
        r = open(outputfile,"w")
        first = False
        for node in new_nodes:
                if(node.t != "output"):
                        r.write(node.shdl(outlabel,new_nodes)+"\n")
                else:
                        if not first:
                                first = True
                                r.write("outputs "+node.shdl(outlabel,new_nodes))
                        else:
                                r.write(" "+node.shdl(outlabel,new_nodes))


def replace_one_wire(nodes, original, new_label):
        for n in nodes:
                for i in range(len(n.inp)):
                        if(n.inp[i] == original):
                                n.inp[i] = new_label
                                return


def rename_all_wires(nodes):
        mapping = dict()
        number = 0
        newnodes = []
        nodes.sort()
        for n in nodes:
                new_outputs = []
                for out in n.output:
                        mapping[out] = number
                        new_outputs.append(number)
                        number = number + 1
                new_inputs = []
                for inp in n.inp:
                        new_inputs.append(mapping[inp])

                newnode = Node(new_inputs,new_outputs,n.t,n.number)
                if(n.t == "gate"):
                        newnode.function_bits = n.function_bits
                newnodes.append(newnode)
        return newnodes


def reduce_fanout_pass(nodes,max_fanout):
        global change_in_pass
        change_in_pass = False
        new_nodes = []
        wire_number = 0
        for n in nodes:
                new_nodes.append(n)
                max_fanout_per_wire = math.floor(max_fanout / max(len(n.output),1))
                for output in n.output:
                        nodes_using_output = []
                        wire_usages = 0
                        for m in nodes:
                                using_output = False
                                for inp in m.inp:
                                        if(inp == output):
                                                wire_usages = wire_usages + 1
                                                using_output = True
                                if using_output:
                                        nodes_using_output.append(m)
                        if wire_usages > max_fanout_per_wire:
                                change_in_pass = True
                                copy_gates_needed = 0
                                while (copy_gates_needed < max_fanout_per_wire and (copy_gates_needed * max_fanout) < wire_usages ):
                                        copy_gates_needed = copy_gates_needed + 1
                                unallocated_wires = wire_usages
                                for i in range(copy_gates_needed):
                                        wire_label = "n"+str(wire_number)
                                        wire_number = wire_number + 1
                                        copygate = Node([output],[wire_label],"gate",0)
                                        copygate.function_bits = [[0,1]]
                                        new_nodes.append(copygate)
                                        wires_should_take = math.floor( wire_usages /  copy_gates_needed)
                                        wires_allocated = 0
                                        for j in range(int(wires_should_take)):
                                                replace_one_wire(nodes,output,wire_label)
                                                unallocated_wires = unallocated_wires - 1
                                                wires_allocated = wires_allocated + 1
                                        if(i == copy_gates_needed - 1):
                                                while( unallocated_wires > 0):
                                                        replace_one_wire(nodes,output,wire_label)
                                                        unallocated_wires = unallocated_wires - 1
                                                        wires_allocated = wires_allocated + 1
        return rename_all_wires(new_nodes)




def main():
    dooutputlabel = False
    fanout = int(sys.argv[3])
    dooutputlabel = False
    print("Reducing "+str(sys.argv[1])+" to "+str(fanout)+" fanout")
    process_file(sys.argv[1],sys.argv[2],fanout,dooutputlabel)


# This is the standard boilerplate that calls the main() function.
if __name__ == '__main__':
    main()
