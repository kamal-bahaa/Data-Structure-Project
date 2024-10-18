#include <iostream>
#include <stack>
#include <queue>
#include <set>
#include <cmath>
#include <vector>
#include <map>
#include "graph.h"
using namespace std;

void Test_Code() {
    graph g;
    int choice;
    string city1, city2;
    float d;
    g.read_from_file();

    do {
        cout << "\nMenu:\n";
        cout << "1-  Add graph (cities and roads)\n";
        cout << "2-  Update graph (add/delete cities and roads)\n";
        cout << "3-  Display graph\n";
        cout << "4-  Perform BFS\n";
        cout << "5-  Perform DFS\n";
        cout << "6-  Find Minimum Spanning Tree (Prim's Algorithm)\n";
        cout << "7-  Find Shortest Path (Dijkstra's Algorithm)\n";
        cout << "8-  Display nearest city\n";
        cout << "9-  Check if connected\n";
        cout << "10- Save Graph\n";
        cout << "11- Exit\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            char ans;
            cout << "An existing graph is present. Do you want to replace it with a new one? (y/n): ";
            cin >> ans;

            if (ans == 'y' || ans == 'Y') {
                g.clear_graph();
                g.add_graph();
            }
            else {
                cout << "Existing graph remains unchanged." << endl;
            }
            break;
        }

        case 2: {
            g.update_graph();
            break;
        }

        case 3:
            g.display_graph();
            break;

        case 4:
            cout << "Enter starting city for BFS: ";
            cin >> city1;
            g.BFS(city1);
            break;

        case 5:
            cout << "Enter starting city for DFS: ";
            cin >> city1;
            g.DFS(city1);
            break;

        case 6:
            cout << "Enter starting city for Minimum Spanning Tree: ";
            cin >> city1;
            g.prim_mst(g.adj_l, city1);
            break;

        case 7:
            cout << "Enter source city: ";
            cin >> city1;
            cout << "Enter destination city: ";
            cin >> city2;
            g.Dijkstra(city1, city2);
            break;

        case 8:
            g.display_nearest_city();
            break;

        case 9:
            cout << "Enter city to check connectivity: ";
            cin >> city1;
            if (g.is_connected(city1))
                cout << "The city " << city1 << " is connected to all other cities.\n";
            else
                cout << "The city " << city1 << " is not connected to all other cities.\n";
            break;

        case 10:
            g.write_to_file(g.adj_l);
            break;

        case 11:
            char saveChoice;
            cout << "Do you want to save the graph before exiting? (y/n): ";
            cin >> saveChoice;
            if (saveChoice == 'y' || saveChoice == 'Y') {
                g.write_to_file(g.adj_l);
                cout << "Graph saved successfully.\n";
            }
            cout << "\nExiting program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);
}



int main()
{
    Test_Code();
    return 0;
}
