from graphviz import Digraph
import sys
import xml.etree.ElementTree as ET

filename = sys.argv[1]

graph = Digraph('expr', format='png', filename=sys.argv[2], node_attr={'color': 'lightblue2', 'style': 'filled'})
graph.attr(size='6,6')

root = ET.parse(filename).getroot()

gid = 1

def parse_sym(nid, node):
    global gid
    graph.node(str(gid), node.attrib['sign'] + node.text)
    graph.edge(str(nid), str(gid))
    gid += 1

def parse_val(nid, node):
    global gid
    graph.node(str(gid), node.text)
    graph.edge(str(nid), str(gid))
    gid += 1

def parse_op(nid, node):
    global gid
    graph.node(str(gid), node.attrib['type'])
    graph.edge(str(nid), str(gid))
    gid += 1
    localgid = gid
    for child in node:
        if child.tag == 'symbol':
            parse_sym(localgid - 1, child)
        elif child.tag == 'value':
            parse_val(localgid - 1, child)
        else:
            parse_op(localgid - 1, child)


graph.node('0', root.attrib['type'])
for child in root:
    if child.tag == 'symbol':
        parse_sym(0, child)
    elif child.tag == 'value':
        parse_val(0, child)
    else:
        parse_op(0, child)

graph.view()
