#pragma once
#include<iostream>
#include <string>
#include<unordered_map>
#include <unordered_set>
#include<queue>
#include<fstream>
#include <stack>
#include<list>
#include <sstream>
using namespace std;

class graph {
    int no_cities;
    int no_roads;
public:

    unordered_map<string, list< pair <string, int>>>adj_l;

    graph();

    string adjust_name(string word);

    bool search_city(string name);
    bool is_connected(string city);

    int get_no_cities();
    int get_no_roads();

    void read_from_file();
    void add_graph();
    void clear_graph();
    void update_graph();
    void add_road(string c1, string c2, float distance);
    void add_new_city(string city_name);
    void delete_city(string c);
    void delete_road(string c1, string c2);
    void display_graph();
    void BFS(string);
    void DFS(string);
    void prim_mst(unordered_map<string, list<pair<string, int>>> g, string startVertex);
    void Dijkstra(string, string);
    void display_nearest_city();
    void write_to_file(unordered_map<string, list<pair<string, int>>> g);

};
