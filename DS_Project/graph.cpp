#include"graph.h"
#include <assert.h>
using namespace std;

graph::graph() {
    no_cities = 0;
    no_roads = 0;
}

string graph::adjust_name(string word) {
    string ans;
    for (int i = 0; i < word.size(); i++) {
        char c = word[i];       //iterate over every character
        if (i == 0)
        {    //capitalize first letter
            char tmp2 = toupper(c);
            ans += (tmp2);
        }
        else
        {
            char tmp3 = tolower(c);//lowercase the rest
            ans += (tmp3);
        }
    }
    return ans;
}

int  graph::get_no_cities() {
    return no_cities;
}

int  graph::get_no_roads() {
    return no_roads;
}

bool graph::search_city(string name) {

    name = adjust_name(name);                         //capitalize first letter and make the rest in lowercase
    return adj_l.find(name) != adj_l.end();           //check if city already exists

}

bool graph::is_connected(string city) {
    city = adjust_name(city);

    return !adj_l[city].empty();
}

void graph::add_graph() {
    float distance;
    int num_cities, num_roads;
    string city_name, c1, c2;
    char anw;

    // 

    cout << "Enter how many cities you want to add: " << endl;//add cities
    cin >> num_cities;

    while (cin.fail() || num_cities < 1) { //handle invalid case
        cout << "Invalid number! ,please try again: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> num_cities;
    }

    for (int i = 1; i <= num_cities; i++) {

        cout << "Enter the name of the city number:" << i << endl;
        cin >> city_name;
        city_name = adjust_name(city_name);
        if (search_city(city_name) == false)
        {
            add_new_city(city_name);
        }
        else
        {
            cout << "this city already exists" << endl;
            i--;
        }

    }

    cout << "Enter how many roads you want to add: " << endl;//add roads

    cin >> num_roads;

    while (num_roads < 0) { //handle invalid case
        cout << "Invalid number! ,please try again: " << endl;
        cin >> num_roads;
    }

    for (int i = 1; i <= num_roads; i++) {
        cout << "Enter the name of the first city along the road number: " << i << endl;
        cin >> c1;
        cout << "Enter the name of the second city along the road number: " << i << endl;
        cin >> c2;
        cout << "Enter the distance (in km) between the two cities in road number: " << i << endl;

        cin >> distance;

        while (cin.fail() || distance <= 0) { //handle invalid case
            cout << "Invalid number! ,please try again: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> distance;
        }
        if (!search_city(c1))
        {
            cout << "City " << c1 << " doesn't exist" << endl;
            cout << "do you want to add this city :" << c1 << " at the graph ? press y to add" << endl;
            cin >> anw;
            switch (anw)
            {
            case 'y':
            case'Y':add_new_city(c1);
                break;
            default:
                break;
            }
            i--;
            continue;
        }
        if (!search_city(c2))
        {
            cout << "City " << c2 << " doesn't exist" << endl;
            cout << "do you want to add this city :" << c2 << " at the graph ? press y to add" << endl;
            cin >> anw;
            switch (anw)
            {
            case 'y':
            case'Y':add_new_city(c2);
                break;
            default:
                break;
            }
            i--;
            continue;
        }
        add_road(c1, c2, distance);
    }
    cout << "Graph added successfully!" << endl;
}

void graph::clear_graph() {
    adj_l.clear();
}

void graph::update_graph() {
    int Choice;
    string city1, city2;
    float d;

    do {
        cout << "\nUpdate Graph Menu:\n";
        cout << "1- Add city\n";
        cout << "2- Add road\n";
        cout << "3- Delete city\n";
        cout << "4- Delete road\n";
        cout << "5- Done updating graph\n";
        cout << "Enter your choice: ";
        cin >> Choice;

        switch (Choice) {
        case 1:
            cout << "Enter city name to add: ";
            cin >> city1;
            add_new_city(city1);
            break;

        case 2:
            cout << "Enter the name of the first city along the road: ";
            cin >> city1;
            cout << "Enter the name of the second city along the road: ";
            cin >> city2;
            cout << "Enter the distance (in km) between the two cities: ";
            cin >> d;
            while (cin.fail() || d <= 0) {
                cout << "Invalid number! Please try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> d;
            }
            add_road(city1, city2, d);
            break;

        case 3:
            cout << "Enter city name to delete: ";
            cin >> city1;
            delete_city(city1);
            break;

        case 4:
            cout << "Enter first city: ";
            cin >> city1;
            cout << "Enter second city: ";
            cin >> city2;
            delete_road(city1, city2);
            break;

        case 5:
            cout << "Finished updating graph.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (Choice != 5);
}

void graph::add_new_city(string city_name)
{
    string word = adjust_name(city_name);
    if (search_city(word) == false)
    {
        adj_l[word];
        no_cities++;
    }
    else
        cout << "City " << city_name << " already exists." << endl;

}

void graph::add_road(string c1, string c2, float distance) {
    c1 = adjust_name(c1);
    c2 = adjust_name(c2);

    if (!search_city(c1)) {
        cout << "City " << c1 << " doesn't exist." << endl;
        return;
    }

    if (!search_city(c2)) {
        cout << "City " << c2 << " doesn't exist." << endl;
        return;
    }
    for (auto& it : adj_l[c1]) {
        if (it.first == c2) {
            cout << "Road between " << c1 << " and " << c2 << " already exists." << endl;
            return;
        }
    }

    adj_l[c1].push_back({ c2, distance });
    adj_l[c2].push_back({ c1, distance });
    no_roads++;
}

void graph::delete_city(string c) {
    c = adjust_name(c);

    // Check if the city exists
    if (!search_city(c)) {
        cout << "City " << c << " does not exist in the graph." << endl;
        return;
    }

    // Remove all roads connected to the city
    for (auto& l : adj_l) {
        if (l.first == c)continue;
        for (auto it = l.second.begin(); it != l.second.end(); it++) {
            if (it->first == c ) {
                l.second.erase(it);
                no_roads--;
                break;
            }
        }
    }
    adj_l.erase(c);
    no_cities--;
}

void graph::delete_road(string c1, string c2) {
    c1 = adjust_name(c1);
    c2 = adjust_name(c2);

    // check if cities exist
    if (adj_l.find(c1) != adj_l.end() && adj_l.find(c2) != adj_l.end()) 
    {
        bool roadFound = false;


        // remove edge from c1 to c2
        for (auto it = adj_l[c1].begin(); it != adj_l[c1].end(); it++) 
        {
            if (it->first == c2)
            {
                adj_l[c1].erase(it);
                roadFound = true;
                break;
            }
        }

        // remove edge from c2 to c1
        for (auto it = adj_l[c2].begin(); it != adj_l[c2].end(); it++) 
        {
            if (it->first == c1) 
            {
                adj_l[c2].erase(it);
                roadFound = true;
                break;
            }
        }

        
        if (!roadFound)
        {
            cout << "There is no road between " << c1 << " and " << c2 << "." << "\n\n";
        }
        else
        {            
            cout << "road deleted";
            no_roads--;
        }
    }

    else 
    {
        cout << "One or both cities do not exist in the graph." << endl;
    }

}

void graph::display_graph()
{
    if (adj_l.empty())
    {
        cout << "the graph is empty ! \n\n";
        return;
    }

    cout << "tha road map is :" << endl;
    unordered_map<string, list< pair <string, int>>> ::iterator it = adj_l.begin();
    list < pair <string, int>> ::iterator it_l;
    for (; it != adj_l.end(); it++)
    {
        cout << it->first << " -> ";

        it_l = it->second.begin(); //iterate over list (second/value of map)
        cout << "\{ ";
        for (; it_l != it->second.end(); it_l++)
        {
            cout << " ( ";
            cout << it_l->first << "," << it_l->second;
            cout << " ) , ";
        }
        cout << "\ } " << endl;
    }

}

void graph::BFS(string city) {
    if (adj_l.empty()) 
    {                    
        cout << "Graph is empty" << endl;
        return;
    }

    city = adjust_name(city);

    if (!search_city(city)) 
    {              
        cout << "City " << city << " doesn't exist in the graph" << endl;
        return;
    }

    unordered_map<string, bool> visited;
    visited[city] = true;

    queue<string> nextCity;
    nextCity.push(city);

    cout << "BFS Traversal starting from city " << city << ":" << endl;

    while (!nextCity.empty()) //loop until the queue is empty
    {            

        string current = nextCity.front();
        nextCity.pop();

        cout << "Visiting city: " << current << endl;

        for (auto& connectedCity : adj_l[current])           // visit all connected cities of the current city
        {       
            if (!visited[connectedCity.first])               // if the connected city hasn't been visited mark it as visited and push it into the queue
            {            
                nextCity.push(connectedCity.first);
                visited[connectedCity.first] = true;
                cout << "   Found a new city: " << connectedCity.first << endl;
            }
        }
    }
}

void graph::DFS(string start) {

    if (adj_l.empty())
    {
        cout << "Graph is empty" << endl;
        return;
    }

    string last = start;
    last = adjust_name(start);
   
    if (!search_city(last))
    {
        cout << "City " << last << " doesn't exist in the graph" << endl;
        return;
    }

    unordered_map<string, bool>visited;
    stack<string>stack;
    list < pair<string, int>>::iterator it;

    stack.push(last);

    while (!stack.empty()) {
        if (!visited[last])
        {
            cout << "DFS Traversal :" << last << endl;
        }

        visited[last] = 1;

        stack.pop();

        it = adj_l[last].begin();

        while (it != adj_l[last].end()) {
            if (visited[it->first] == 0)
                stack.push(it->first);
            it++;
        }
        if (!stack.empty())
            last = stack.top();
    }

}

void graph::prim_mst(unordered_map<string, list<pair<string, int>>> g, string startVertex) {
    startVertex = adjust_name(startVertex);
    unordered_map<string, list<pair<string, int>>>graph;
    graph = g;
    unordered_map<string, int> key;
    unordered_map<string, string> parent;
    unordered_map<string, bool> inMST;
    unordered_map<string, int>weight_edge;
    int INF = INT_MAX;
    int total_weight = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    pq.push({ 0, startVertex });
    key[startVertex] = 0;

    for (auto vertex : graph) {
        string v = vertex.first;
        if (v != startVertex) {
            key[v] = INF;
            inMST[v] = false;
        }
    }

    while (!pq.empty()) {

        string u = pq.top().second;
        int to_weight = pq.top().first;
        pq.pop();
        if (inMST[u]) {
            continue; // Skip if already included in MST
        }

        inMST[u] = true;
        total_weight += to_weight;


        for (auto edge : graph.at(u)) {
            string v = edge.first;
            int weight = edge.second;

            // If v is not in MST and weight of (u,v) is smaller than current key of v
            if (!inMST[v] && weight < key[v]) {

                key[v] = weight;
                pq.push({ key[v], v });
                parent[v] = u;
                weight_edge[u + "-" + v] = weight;
            }
        }
    }

    // Print the edges of MST
    cout << "Edges of Minimum Spanning Tree:" << endl;
    for (auto vertex : parent) {


        cout << vertex.second << " - " << vertex.first << " - " << weight_edge[vertex.second + "-" + vertex.first] << endl;

    }
    cout << "Total weight of the Minimum Spanning Tree: " << total_weight << endl;
}

void graph::Dijkstra(string city1, string city2) {
    city1 = adjust_name(city1);
    city2 = adjust_name(city2);

    // Check if cities exist in the graph
    if (!search_city(city1)) {
        cout << "City " << city1 << " doesn't exist in the graph." << endl;
        return;
    }
    if (!search_city(city2)) {
        cout << "City " << city2 << " doesn't exist in the graph." << endl;
        return;
    }

    unordered_set<string> visited;

    unordered_map<string, int> distance;

    for (auto& city : adj_l) {
        distance[city.first] = INT_MAX;
    }

    distance[city1] = 0;

    while (true) {
        string current_city;
        int min_distance = INT_MAX;

        for (auto& city : adj_l) {
            if (visited.find(city.first) == visited.end() && distance[city.first] < min_distance) {
                min_distance = distance[city.first];
                current_city = city.first;
            }
        }

        if (min_distance == INT_MAX)
            break;

        visited.insert(current_city);



        for (auto& neighbor : adj_l[current_city]) {

            if (visited.find(neighbor.first) == visited.end()) {

                distance[neighbor.first] = min(distance[neighbor.first], distance[current_city] + neighbor.second);
            }
        }




    }
    cout << "Shortest distance from " << city1 << " to " << city2 << " is: ";
    if (distance[city2] == INT_MAX)
        cout << "Not reachable" << endl;
    else
        cout << distance[city2] << " Km." << endl;

}

void graph::display_nearest_city() {
    string city;
    stack<pair<string, int>> nearest_cities;
    cout << "Choose starting city: ";
    cin >> city;
    city = adjust_name(city);
    if (!search_city(city))
        cout << "City " << city << " doesn't exist.";
    else if (!is_connected(city))
        cout << "No nearby cities available.";
    else {
        nearest_cities.push(make_pair(adj_l[city].begin()->first, adj_l[city].begin()->second));
        auto it = adj_l[city].begin();
        it++;
        for (it; it != adj_l[city].end(); it++) {
            if (it->second == nearest_cities.top().second)
                nearest_cities.push(make_pair(it->first, it->second));
            else if (it->second < nearest_cities.top().second) {
                while (!nearest_cities.empty())
                    nearest_cities.pop();
                nearest_cities.push(make_pair(it->first, it->second));
            }
        }
        if (nearest_cities.size() == 1)
            cout << "Nearest city is " << nearest_cities.top().first << " that is " << nearest_cities.top().second << " km far from your location.";
        else {
            cout << "Nearest cities are:\n";
            int distance = nearest_cities.top().second;
            while (!nearest_cities.empty()) {
                cout << nearest_cities.top().first << ".\n";
                nearest_cities.pop();
            }
            cout << "(" << distance << " km far from your location)" << endl;
        }
    }
}

void graph::write_to_file(unordered_map<string, list<pair<string, int>>> graph) {
    ofstream f;
    f.open("graph.txt");
    if (!f.is_open()) {
        cout << "Failed to open file   or writing." << endl;
        return;
    }
    bool found = 0;
    for (auto vertex : graph) {
        string u = vertex.first;
        list<pair<string, int>> edges = vertex.second;
        found = 0;
        for (auto edge : edges) {
            string v = edge.first;
            int weight = edge.second;
            f << u << " " << v << " " << weight << endl;
            found = 1;
        }
        if (found == 0) { f << u << endl; }

    }
    f.close();

}

void graph::read_from_file() {
    ifstream file;
    file.open("graph.txt");
    if (!file.is_open()) {
        cout << "Failed to open file for reading." << endl;
        return;
    }
    string u, v;
    int weight;

    string line;
    while (getline(file, line)) {

        stringstream ss(line);
        ss >> u >> v >> weight;


        if (ss.fail()) {
            adj_l[u];
        }
        else {
            adj_l[u].push_back({ v, weight });
        }
    }

    file.close();
    // cout << "Graph data has been read successfully." << endl;


}