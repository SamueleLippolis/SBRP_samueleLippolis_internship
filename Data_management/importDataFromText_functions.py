# ------ Lib 

import networkx as nx  # Library for creating, manipulating, and studying the structure, dynamics, and functions of complex networks.
import pandas as pd  # Library for data manipulation and analysis. Provides data structures and functions for efficiently working with structured data.
import csv  # Library for reading and writing CSV files. Provides functionality to work with comma-separated values.
import ast  # Library for parsing and evaluating Python literals. Provides functions to safely evaluate strings containing Python expressions.
import os  # Library for interacting with the operating system. Provides functions for file and directory manipulation, environment variables, etc.



# ------ Import

# Parses the content of a graph file and returns the nodes and edges.
def parse_graph(file_content):
    """
    Parses the content of a graph file and returns the nodes and edges.

    Args:
        file_content (str): The content of the graph file.

    Returns:
        tuple: A tuple containing two dictionaries. The first dictionary contains the nodes, 
               where the keys are the node IDs and the values are dictionaries representing 
               the node properties. The second dictionary contains the edges, where each 
               element is a dictionary representing an edge.

    """
    nodes = {}
    edges = []

    current_node = None
    current_edge = None

    for line in file_content.splitlines():
        line = line.strip()
        if line.startswith("node"):
            current_node = {}
        elif line.startswith("edge"):
            current_edge = {}
        elif line.startswith("id"):
            current_node['id'] = int(line.split()[1])
        elif line.startswith("label"):
            current_node['label'] = line.split()[1].strip('"')
        elif line.startswith("pos"):
            if 'pos' in current_node:
                current_node['pos'].append(float(line.split()[1]))
            else:
                current_node['pos'] = [float(line.split()[1])]
        elif line.startswith("tipologia"):
            current_node['tipologia'] = line.split()[1].strip('"')
        elif line.startswith("locazione"):
            current_node['locazione'] = line.split()[1].strip('"')
        elif line.startswith("citta"):
            current_node['citta'] = int(line.split()[1])
        elif line.startswith("ragazzi"):
            if 'ragazzi' in current_node:
                current_node['ragazzi'].append(int(line.split()[1]))
            else:
                current_node['ragazzi'] = [int(line.split()[1])]
        elif line.startswith("source"):
            current_edge['source'] = int(line.split()[1])
        elif line.startswith("target"):
            current_edge['target'] = int(line.split()[1])
        elif line.startswith("weight"):
            current_edge['weight'] = float(line.split()[1])
        elif line.startswith("time"):
            current_edge['time'] = float(line.split()[1])
        elif line == "]":
            if current_node is not None:
                # Ensure ragazzi list has 4 elements if necessary
                if 'ragazzi' in current_node:
                    while len(current_node['ragazzi']) < 4:
                        current_node['ragazzi'].append(0)
                nodes[current_node['id']] = current_node
                current_node = None
            if current_edge is not None:
                edges.append(current_edge)
                current_edge = None

    return nodes, edges


# Function to create a graph from the nodes and edges
def create_graph(nodes, edges):
    G = nx.DiGraph()  # Create a directed graph

    for node_id, node_data in nodes.items():
        G.add_node(node_id, **node_data)

    for edge in edges:
        G.add_edge(edge['source'], edge['target'], weight=edge['weight'], time=edge['time'])

    return G
    

# ------ Write on csv
def read_file(file_path):
    with open(file_path, 'r') as file:
        return file.read()

def parse_graph(file_content):
    nodes = {}
    edges = []

    current_node = None
    current_edge = None

    for line in file_content.splitlines():
        line = line.strip()
        if line.startswith("node"):
            current_node = {}
        elif line.startswith("edge"):
            current_edge = {}
        elif line.startswith("id"):
            current_node['id'] = int(line.split()[1])
        elif line.startswith("label"):
            current_node['label'] = line.split()[1].strip('"')
        elif line.startswith("pos"):
            if 'pos' in current_node:
                current_node['pos'].append(float(line.split()[1]))
            else:
                current_node['pos'] = [float(line.split()[1])]
        elif line.startswith("tipologia"):
            current_node['tipologia'] = line.split()[1].strip('"')
        elif line.startswith("locazione"):
            current_node['locazione'] = line.split()[1].strip('"')
        elif line.startswith("citta"):
            current_node['citta'] = int(line.split()[1])
        elif line.startswith("ragazzi"):
            if 'ragazzi' in current_node:
                current_node['ragazzi'].append(int(line.split()[1]))
            else:
                current_node['ragazzi'] = [int(line.split()[1])]
        elif line.startswith("source"):
            current_edge['source'] = int(line.split()[1])
        elif line.startswith("target"):
            current_edge['target'] = int(line.split()[1])
        elif line.startswith("weight"):
            current_edge['weight'] = float(line.split()[1])
        elif line.startswith("time"):
            current_edge['time'] = float(line.split()[1])
        elif line == "]":
            if current_node is not None:
                # Ensure ragazzi list has 4 elements if necessary
                if 'ragazzi' in current_node:
                    while len(current_node['ragazzi']) < 4:
                        current_node['ragazzi'].append(0)
                nodes[current_node['id']] = current_node
                current_node = None
            if current_edge is not None:
                edges.append(current_edge)
                current_edge = None

    return nodes, edges

def create_graph(nodes, edges):
    G = nx.DiGraph()  # Create a directed graph

    for node_id, node_data in nodes.items():
        G.add_node(node_id, **node_data)

    for edge in edges:
        G.add_edge(edge['source'], edge['target'], weight=edge['weight'], time=edge['time'])

    return G


def write_edges_to_csv(edges, folder_name, filename):
    try:
        # Ensure the folder exists
        if not os.path.exists(folder_name):
            os.makedirs(folder_name)

        # Create the full file path
        file_path = os.path.join(folder_name, filename)

        if not edges:
            return

        # Determine CSV headers
        headers = list(edges[0].keys())

        # Write the data to a CSV file
        with open(file_path, 'w', newline='', encoding='utf-8') as csvfile:
            writer = csv.DictWriter(csvfile, fieldnames=headers)
            
            # Write the header
            writer.writeheader()

            # Write the rows
            for edge in edges:
                writer.writerow(edge)
        
    except Exception as e:
        print("Error:", e)


# Read the file content
def write_nodes_to_csv(nodes, folder_name, filename):
    # Create folder if it doesn't exist
    os.makedirs(folder_name, exist_ok=True)
    
    # Construct the full file path
    file_path = os.path.join(folder_name, filename)
    
    with open(file_path, mode='w', newline='') as file:
        writer = csv.writer(file)
        
        for key, node in nodes.items():
            row = [
                key,
                node.get('id'),
                node.get('label'),
                node['pos'][0],
                node['pos'][1],
                node['tipologia']
            ]
            
            # Add 'ragazzi' values if 'tipologia' is 'fermata'
            if node['tipologia'] == 'fermata':
                row.extend(node.get('ragazzi', []))
            else:
                row.extend([0, 0, 0, 0])
            
            writer.writerow(row)




# ------ Distance and time matrices 

def read_excel_matrix(file_path):
    try:
        # Read the Excel file into a DataFrame
        df = pd.read_excel(file_path, header=None)

        # Convert the DataFrame to a 2D list
        distance_matrix = df.values.tolist()

        return distance_matrix

    except Exception as e:
        print("Error:", e)



def read_excel_matrix(file_path):
    try:
        # Read the Excel file into a DataFrame
        df = pd.read_excel(file_path, header=None)

        # Convert the DataFrame to a 2D list
        distance_matrix = df.values.tolist()

        return distance_matrix

    except Exception as e:
        print("Error:", e)


def write_matrix_to_csv(matrix, folder_name, filename):
    try:
        # Ensure the folder exists
        if not os.path.exists(folder_name):
            os.makedirs(folder_name)

        # Create the full file path
        file_path = os.path.join(folder_name, filename)

        # Write the distance matrix to a CSV file
        with open(file_path, 'w', newline='', encoding='utf-8') as csvfile:
            writer = csv.writer(csvfile)
            
            # Write each row of the distance matrix
            for row in matrix:
                writer.writerow(row)
                
        print(f"Matrix has been written to {file_path}")
        
    except Exception as e:
        print("Error:", e)

