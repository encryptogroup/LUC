import sys
import re
import math
import random

allnodes = {}


class Node:
    def __init__(self, inp, output, t, number):
        self.inp = inp
        self.output = output
        self.t = t
        self.number = number

    def shdl(self):
        if self.t == "input":
            return str(self.output[0]) + " input"
        if self.t == "gate":
            fb = []
            for bits in self.function_bits:
                fb.append(" ".join([str(a) for a in bits]))
            return (
                " ".join([str(a) for a in self.output])
                + " gate arity "
                + str(len(self.inp))
                + " table [ "
                + " ] [ ".join(fb)
                + " ] inputs [ "
                + " ".join([str(a) for a in self.inp])
                + " ]"
            )
        return str(self.inp[0])

    def __lt__(self, other):
        if self.t == "input" and other.t == "input":
            return int(self.output[0]) < int(other.output[0])
        return (
            (self.t == "input" and other.t == "gate")
            or (self.t == "gate" and other.t == "output")
            or (self.t == "input" and other.t == "output")
        )

    def __repr__(self):
        return (
            "[ "
            + ", ".join([str(a) for a in self.inp])
            + " ] "
            + str(self.t)
            + " [ "
            + ", ".join([str(a) for a in self.output])
            + " ]"
        )


change_in_pass = True
fani = {}


def has_path(a, b, nodes):
    if a == b:
        return True
    successors = []
    for n in nodes:
        if has_edge(a, n):
            successors.append(n)
    for succ in successors:
        if has_path(succ, b, nodes):
            return True
    return False


def process_file(inputfile, outputfile, max_fanin, max_fanout, targetmerges, max_real):
    global change_in_pass
    global fanin
    global fanout
    global allnodes
    f = open(inputfile, "r")
    original_nodes = []
    for line in f.readlines():
        elements = re.split(r"\s*[=,()\n\s]\s*", line)
        if elements[1] == "input":
            original_nodes.append(Node([], [int(elements[0])], "input", 0))
        elif "gate" in elements:
            i = 0
            outputs = []
            while elements[i] != "gate":
                outputs.append(int(elements[i]))
                i = i + 1
            arity = int(elements[i + 2])
            i = i + 5
            function_bits = []
            for j in range(len(outputs)):
                fb = []
                for k in range(2**arity):
                    b = elements[i + j * (2**arity + 2) + k]
                    fb.append(b)
                function_bits.append(fb)
            i = -3
            inputs = []
            while elements[i] != "[":
                inputs.append(int(elements[i]))
                i = i - 1
            # preserve order
            inputs.reverse()
            newnode = Node(inputs, outputs, "gate", 0)
            newnode.function_bits = function_bits
            original_nodes.append(newnode)
        elif "outputs" in elements:
            del elements[0]
            if elements[-1] == "":
                del elements[-1]
            for e in elements:
                original_nodes.append(Node([int(e)], [], "output", 0))
    original_nodes = create_multi_input_output(
        original_nodes, max_fanin, max_fanout, targetmerges, max_real
    )
    # list is topo sorted
    # original_nodes = topo_sort(original_nodes)
    original_nodes.sort()
    original_nodes = rename_all_wires(original_nodes)
    r = open(outputfile, "w")
    first = False
    for node in original_nodes:
        if node.t != "output":
            r.write(node.shdl() + "\n")
        else:
            if not first:
                first = True
                r.write("outputs " + node.shdl())
            else:
                r.write(" " + node.shdl())
    quit()


def input_interface(collection):
    inputs = []
    for node in collection:
        for inp in node.inp:
            if inp not in inputs:
                is_input_to_collection = True
                for node2 in collection:
                    if inp in node2.output:
                        is_input_to_collection = False
                if is_input_to_collection:
                    inputs.append(inp)
    return inputs


def output_interface(collection, nodes):
    outputs = []
    for node in collection:
        for out in node.output:
            # check if output not already included
            if out not in outputs:
                # check if there is a node outside of the collection that uses this output
                for node2 in nodes:
                    if (node2 not in collection) and (out in node2.inp):
                        outputs.append(out)
                        break
    return outputs


# only works for two nodes
def order_collection(collection):
    ordered_collection = []
    if has_edge(collection[0], collection[1]):
        ordered_collection.append(collection[0])
        ordered_collection.append(collection[1])
    else:
        ordered_collection.append(collection[1])
        ordered_collection.append(collection[0])
    return ordered_collection


def merge_nodes(collection, nodes):
    inputs = input_interface(collection)
    outputs = output_interface(collection, nodes)
    function_bits = []
    print(collection)
    ordered_collection = order_collection(collection)
    print(ordered_collection)
    print(inputs)
    print(outputs)
    for o in outputs:
        bits = []
        for i in range(2 ** len(inputs)):
            value = {}
            binary = ("{0:b}".format(i)).zfill(len(inputs))
            x = 0
            # this needed to be reversed because of how the inputs are ordered
            binary = binary[::-1]
            
            for inp in inputs:
                value[inp] = int(binary[x])
                x = x + 1
            # evaluate ordered collection
            for node in ordered_collection:
                p = 0
                y = 0
                for inputwire in node.inp:
                    p += (2 ** y) * value[inputwire]
                    y = y + 1
                h = 0
                for out in node.output:
                    value[out] = int(node.function_bits[h][p])
                    h = h + 1
            bits.append(value[o])
        function_bits.append(bits)
    new_node = Node(inputs, outputs, "gate", 0)
    new_node.function_bits = function_bits
    return new_node


def topo_sort(nodes):
    # result
    L = []
    # initial set
    S = []
    mark = {}
    for m in nodes:
        if len(m.inp) == 0:
            S.append(m)
        for n in nodes:
            for inp in n.inp:
                if inp in m.output:
                    mark[(m, inp, n)] = False
    while len(S) > 0:
        n = S.pop()
        L.append(n)
        for m in nodes:
            if m.t == "output":
                continue
            edge = has_edge(n, m)
            if edge == False:
                continue
            if not mark[edge]:
                mark[edge] = True
                no_other = True
                # check if there is another edge
                for k in nodes:
                    if k == n:
                        continue
                    edge2 = has_edge(k, m)
                    if edge2 == False:
                        continue
                    if not mark[edge2]:
                        no_other = False
                if no_other:
                    S.append(m)
    for m in nodes:
        if m.t == "output":
            L.append(m)
    return L


def successors(node, nodes):
    successors = []
    for n in nodes:
        if node.output[0] in n.inp:
            successors.append(n)
    return successors


def predecessors(node, nodes):
    predecessors = []
    for n in nodes:
        for out in n.output:
            if out in node.inp:
                predecessors.append(n)
                break
    return predecessors


def has_edge(m, n):
    for out in m.output:
        if out in n.inp:
            return (m, out, n)
    return False


fi = {}


def real_fanin(collection):
    global fi
    if str(collection) in fi:
        return fi[str(collection)]
    inputs = input_interface(collection)
    return len(inputs)


def max_fanout_larger(collection, nodes, actual_max_fanout):
    outputs = output_interface(collection, nodes)
    max_fanout = 0
    for o in outputs:
        fanout = 0
        for node in nodes:
            if node not in collection:
                if o in node.inp:
                    fanout = fanout + 1
        max_fanout = max(max_fanout,fanout)
        if max_fanout > actual_max_fanout:
            return True
    return False


def get_group(node, node_groups):
    real_group = node_groups[0]
    for group in node_groups:
        if node in group:
            real_group = group
            break
    return node_groups.index(real_group)


gr = {}


def group_range(collection, node_groups):
    global gr
    if str(collection) in gr:
        return gr[str(collection)]
    max_group = 0
    for node in collection:
        group_index = get_group(node, node_groups)
        if group_index > max_group:
            max_group = group_index
    gr[str(collection)] = max_group
    return max_group


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
        newnode = Node(new_inputs, new_outputs, n.t, n.number)
        if n.t == "gate":
            newnode.function_bits = n.function_bits
        newnodes.append(newnode)
    return newnodes


def nodegroups(topo_sorted_nodes):
    global gr
    gr = {}
    node_groups = []
    current_group = []
    # seperate by topological layers
    for n in topo_sorted_nodes:
        if n.t == "gate":
            new_group = False
            for m in current_group:
                if has_edge(m, n):
                    # new group
                    node_groups.append(current_group)
                    current_group = [n]
                    new_group = True
                    break
            if not new_group:
                current_group.append(n)
    node_groups.append(current_group)
    return node_groups


def output_used_in_layer(layer, node):
    for output in node.output:
        for node2 in layer:
            if output in node2.inp:
                return True
    return False


def insert_into(layers, new_node):
    largest_layer = -1
    for inp in new_node.inp:
        for layer in layers:
            Found = False
            for node in layer:
                if inp in node.output:
                    index = layers.index(layer)
                    if index > largest_layer:
                        largest_layer = index
                        Found = True
                    break
            if Found:
                break
    # print(largest_layer)
    if len(layers) > (largest_layer + 1):
        if output_used_in_layer(layers[largest_layer + 1], new_node):
            layers.insert(largest_layer + 1, [new_node])
        else:
            layers[largest_layer + 1].append(new_node)
    else:
        layers.insert(largest_layer + 1, [new_node])
    return layers


def remove_from(layers, node):
    res = [[ele for ele in sub if ele != node] for sub in layers]
    new_layers = list(filter(None, res))
    return new_layers


layer_ind = {}


def get_layer_index(layers, node):
    global layer_ind
    if node in layer_ind:
        return layer_ind[node]
    index = 0
    for l in layers:
        if node in l:
            ind = index
            layer_ind[node] = ind
            return ind
        index = index + 1


def get_neighborhood(layers, node):
    same_layer = []
    for l in layers:
        if node in l:
            same_layer = l
            break
    return same_layer


def get_neighborhood2(layers, node):
    next_layer = []
    found = False
    for l in layers:
        if found:
            next_layer = l
            break
        if node in l:
            found = True
    return next_layer


d = {}


def depth(node, nodes, show=False):
    global d
    if node in d:
        return d[node]
    if len(node.inp) == 0:
        d[node] = 0
        return 0
    max_depth = 0
    preds = predecessors(node, nodes)
    for pred in preds:
        p = depth(pred, nodes)
        if max_depth < p:
            max_depth = p
    d[node] = max_depth + 1
    return max_depth + 1


def create_multi_input_output(
    nodes, max_fanin, max_fanout, targetmerges, max_real_outputs
):
    global layer_ind
    global gr
    global d
    new_nodes = []
    print("Toposorting")
    # topo_sorted_nodes = topo_sort(nodes)
    topo_sorted_nodes = nodes[:]
    selectable_nodes = []
    print("Toposorting done")
    # seperate by topological layers
    for n in topo_sorted_nodes:
        if n.t == "gate":
            selectable_nodes.append(n)
    # print(node_groups)
    # preselect inputs and outputs
    final_outputs = []
    for node in nodes:
        if node.t == "input":
            new_nodes.append(node)
        if node.t == "output":
            final_outputs.append(node)

    print("Inputs: " + str(len(new_nodes)))
    print("Gates: " + str(len(selectable_nodes)))
    print("Outputs: " + str(len(final_outputs)))
    print("Starting merging process")
    merges = 0
    # target_merges = int(math.sqrt(len(selectable_nodes)))
    # target_merges = len(selectable_nodes)
    i = 0
    got_merge = True
    got_change = True
    r = 0
    # result = topo_sort((new_nodes+selectable_nodes+final_outputs))
    # selectable_nodes = []
    # for n in result:
    # 	if n.t == "gate":
    # 		selectable_nodes.append(n)
    clone_list = (new_nodes + selectable_nodes + final_outputs)[:]
    print("Reordering")
    # look for more efficient
    # selectable_nodes.sort(key=lambda x: depth(x,clone_list))

    layers = []
    for node in selectable_nodes:
        layers = insert_into(layers, node)

    # print(layers)
    print("Merging Nodes")
    while merges < targetmerges:
        r = r + 1

        # i = random.randint(0,len(selectable_nodes)-1)
        # flatten layers
        selectable_nodes = [item for sublist in layers for item in sublist]
        i = (i + 1) % len(selectable_nodes)
        print(
            "Round "
            + str(r)
            + ":"
            + " Merges: "
            + str(merges)
            + "/"
            + str(targetmerges)
            + " "
            + str(i)
            + "/"
            + str(len(selectable_nodes))
        )
        if i == 0 and not got_change:
            break
        elif i == 0:
            got_change = False
        got_merge = False
        a = selectable_nodes[i]
        neighborhood = get_neighborhood(layers, a)
        neighborhood2 = get_neighborhood2(layers, a)
        x = get_layer_index(layers, a)
        # here instead use length of next k groups
        for b in neighborhood:
            if a == b:
                continue
            # this could be faster
            y = x
            if can_merge(
                [a],
                [b],
                (new_nodes + selectable_nodes + final_outputs),
                max_fanin,
                max_fanout,
                max_real_outputs,
                x,
                y,
            ):
                got_merge = True
                break
        if not got_merge:
            for b in neighborhood2:
                if a == b:
                    continue
                # this could be faster
                y = x + 1
                if can_merge(
                    [a],
                    [b],
                    (new_nodes + selectable_nodes + final_outputs),
                    max_fanin,
                    max_fanout,
                    max_real_outputs,
                    x,
                    y,
                ):
                    got_merge = True
                    break

        if got_merge:
            got_change = True
            merges = merges + 1
            new_node = merge_nodes(
                [a, b], (new_nodes + selectable_nodes + final_outputs)
            )
            layers = remove_from(layers, a)
            layers = remove_from(layers, b)
            layers = insert_into(layers, new_node)
            # manually set group range of merged node
            fi = {}
            d = {}
            layer_ind = {}
    print("Done collecting")

    selectable_nodes = [item for sublist in layers for item in sublist]
    for n in selectable_nodes:
        new_nodes.append(n)

    for node in final_outputs:
        new_nodes.append(node)
    return new_nodes


def insert_in_topo_order(m, selectable_nodes):
    de = depth(m, selectable_nodes)
    index = 0
    i = 0
    for n in selectable_nodes:
        i = i + 1
        if depth(n, selectable_nodes) == de:
            index = i
            break
    selectable_nodes.insert(index, m)
    return selectable_nodes


# check if all inputs of a are outputs of b or inputs of b
def all_inputs_in(a, b, nodes):
    # these are single nodes
    inputsa = a[0].inp
    inputsb = b[0].inp
    outputsb = b[0].output
    merged_list = outputsb + inputsb
    for inp in inputsa:
        if inp not in merged_list:
            return False
    return True


# checks wether or not we may merge two collections together


def can_merge(a, b, nodes, max_fanin, max_fanout, max_different_outputs, x, y):
    potential_match = a + b
    rfi = real_fanin(potential_match)
    if rfi > max_fanin:
        return False
    rfo = max_fanout_larger(potential_match, nodes, max_fanout)

    if rfo:
        return False
    rsfo = len(output_interface(potential_match, nodes))
    if rsfo > max_different_outputs:
        return False
    return True


def main():

    if not(len(sys.argv) == 7):
        print("Usage: [input_file] [output_file] [fanin] [fanout_per_gate] [number_of_outputs] [target_number_of_merges]")
        exit()
    print(sys.argv)
    fanin = int(sys.argv[3])
    fanout_per_output = int(sys.argv[4])
    targetmerges = int(sys.argv[6])
    max_real_outputs = int(sys.argv[5])
    print(
        "Collecting "
        + str(sys.argv[1])
        + " to have "
        + str(fanin)
        + " fanin "
        + str(fanout_per_output)
        + " fanout per gate "
        + str(targetmerges)
        + " targetmerges"
    )
    process_file(
        sys.argv[1], sys.argv[2], fanin, fanout_per_output, targetmerges, max_real_outputs
    )


# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
    main()
