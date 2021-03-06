#include <iostream>
#include <list>
#include <string>
using namespace std;

template<typename T, typename C>
class graph {
public:
    class vertex;
    class edge;    

    class vertex {
    public:
        T data;
        list<edge> neighbors;
        
        bool visited;
        double cost;
        double estimated_cost;
        vertex* pred;

        vertex() {
            visited = false;
            cost = 0;
            estimated_cost = 0;
            pred = NULL;
        }

        bool operator>(const vertex &rhs) {
            if (this.estimated_cost > rhs.estimated_cost)
                return true;
            return false;
        }
    };

    class edge {
    public:
        vertex* start;
        vertex* end;
        C cost;

        // Create a new edge from a to b with weight w
        edge(vertex* a, vertex* b, C c) {
            start = a;
            end = b;
            cost = c;
        }
    };

    list<vertex*> vertices;

public:
    graph() {
        vertices = list<vertex*>();
    }

    // Add a vertex with data value x to the graph
    // Each vertex's data value must be unique
    bool add_vertex(T x) {
        // Check that vertex is not in graph already
        for (typename list<vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
            vertex* v = *it;
            if (v->data == x) {
                cout << "Element already in table" << endl;
                return false;
            }
        }

        // Add new vertex to graph
        vertex* v = new vertex();
        v->data = x;
        vertices.push_back(v);
        return true; 
    }

    // Add an edge between two vertices with a cost
    bool add_edge(T a, T b, C c) {
        // Disallow edges to self
        if (a == b)
            return false;

        //Find vertices in graph with data a and b
        vertex* s = NULL;
        vertex* e = NULL;
        for (typename list<vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
            vertex* v = *it;
            if (v->data == a)
                s = v;
            else if (v->data == b)
                e = v;
        }
        
        // Create vertices if they are not found
        if (s == NULL) {
            //cout << a << " does not exist, creating" << endl;
            add_vertex(a);
            s = vertices.back();
        }
        if (e == NULL) {
            //cout << b << " does not exist, creating" << endl;
            add_vertex(b);
            e = vertices.back();
        }

        if (s != NULL && e != NULL) {
            edge e1 = edge(s, e, c);
            edge e2 = edge(e, s, c);
            s->neighbors.push_back(e1);
            e->neighbors.push_back(e2);
            return true;
        }
        else
            return false;
    }
    
    vertex* find_vertex(string a) {
        for (typename list<vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
            vertex* v = *it;
            if (v->data == a)
                return v;
        }
        return NULL;
    }

    void print() {
        for (typename list<vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
            vertex* v = *it;
            cout << v->data << endl;
            for (typename list<edge>::const_iterator it2 = v->neighbors.begin(); it2 != v->neighbors.end(); ++it2) {
                edge e = *it2;
                cout << e.end->data << " : " << e.cost << endl;
            }
            cout << endl;
        }
    }
};
