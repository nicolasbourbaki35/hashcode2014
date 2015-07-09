#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/subgraph.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <vector>

int64_t NUM_OF_EDGES = 0;
uint64_t NUM_OF_VERTICES = 0;
uint64_t TIME = 0;
uint64_t NUM_OF_CARS = 0;
uint64_t INITIAL_VERTEX = 0;

std::random_device rd;
std::default_random_engine e1(rd());

namespace boost {
    enum edge_time_t { edge_time };
    enum edge_length_t { edge_length };
    enum edge_visited_t { edge_visited };
    enum edge_bidirectional_t { edge_bidiractional };

    BOOST_INSTALL_PROPERTY(edge, time);
    BOOST_INSTALL_PROPERTY(edge, length);
    BOOST_INSTALL_PROPERTY(edge, visited);
    BOOST_INSTALL_PROPERTY(edge, bidirectional);
    
    enum vertex_latitude_t { vertex_latitude };
    enum vertex_longitude_t { vertex_longitude };
    enum vertex_originalindex_t { vertex_originalindex };

    BOOST_INSTALL_PROPERTY(vertex, latitude);
    BOOST_INSTALL_PROPERTY(vertex, longitude);
    BOOST_INSTALL_PROPERTY(vertex, originalindex);
}

typedef boost::property<boost::edge_length_t, uint32_t> Length;
typedef boost::property<boost::edge_time_t, uint32_t, Length> Time;
typedef boost::property<boost::edge_weight_t, double, Time> Weight;
typedef boost::property<boost::edge_visited_t, bool, Weight> Visited;
typedef boost::property<boost::edge_bidirectional_t, bool, Visited> Bidirectional;
typedef boost::property<boost::edge_index_t, uint32_t, Bidirectional> EdgeProperty;

typedef boost::property<boost::vertex_longitude_t, double> Longitude;
typedef boost::property<boost::vertex_latitude_t, double, Longitude> Latitude;
typedef boost::property<boost::vertex_originalindex_t, int, Latitude> OriginalIndex;
typedef boost::property<boost::vertex_index_t, int, OriginalIndex> VertexProperty;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty, EdgeProperty> ParentGraph;
typedef boost::subgraph<ParentGraph > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;

//////////////////////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////////////////////

void printGraph(Graph & g)
{
    auto es = boost::edges(g);
    std::copy(es.first, es.second, std::ostream_iterator<Graph::edge_descriptor>{std::cout, "\n"});
    
    auto vs = boost::vertices(g);
    std::copy(vs.first, vs.second, std::ostream_iterator<Graph::vertex_descriptor>{std::cout, "\n"});
}

/*
bool isPointOnLeftOfLine(Point const&  start, Point const& end, Point const& x)
{
    return (end.Lat-start.Lat)*(x.Long-start.Long) 
            - (end.Long-start.Long)*(x.Lat-start.Lat) >= 0;
}

PointVector convex_hull(const PointVector& points)
{
    PointVector res;
    
    if (points.size() == 0)
        return res;
    
    double min_long = std::numeric_limits<double>::max();
    uint32_t min_index = 0, i = 0;
    for(auto point : points)
    {
        if (point.Long > min_long)
        {
            min_long = point.Long;
            min_index = i;
        }
        ++i;
    }
   
    std::cout << points[min_index] << std::endl;
     
    auto pointOnHull = points[min_index];

    i = 0;
    auto endpoint = points[i];
    
    do
    {
        res.push_back(pointOnHull);
        
        for (uint32_t j=1; i<points.size(); ++j)
        {
            if ((endpoint == pointOnHull) || 
                isPointOnLeftOfLine(res[i], endpoint, points[j]))
            {
                endpoint = points[j];   // found greater left turn, update endpoint
            }
        }
       
        std::cout << i << std::endl; 
        ++i;
        pointOnHull = endpoint;
    }
    while (endpoint == res[0]);
    
    return res; 
}
*/

//////////////////////////////////////////////////////////////////////////////////////

bool readGraph(const std::string & path, Graph & g)
{
    bool result = true;
    std::ifstream f(path);
    
    if (!f.is_open())
    {
        std::cout << " Cannot open file " << path << std::endl;
        return false;
    }
    
    f >> NUM_OF_VERTICES >> NUM_OF_EDGES >> TIME >> NUM_OF_CARS >> INITIAL_VERTEX;
    
    std::string line; 

    // Coordinates
    auto longitude_prop = boost::get(boost::vertex_longitude_t(), g);
    auto latitude_prop = boost::get(boost::vertex_latitude_t(), g);
    auto originalindex_prop = boost::get(boost::vertex_originalindex_t(), g);
    
    for(auto i=0u; i<NUM_OF_VERTICES; ++i)
    {
        vertex_t v = boost::add_vertex(g);
        
        double latitude, longitude;
         
        f >> latitude >> longitude;

        boost::put(longitude_prop, v, longitude);
        boost::put(latitude_prop, v, latitude);
        boost::put(originalindex_prop, v, i);
    }    

    // Edges
    auto time_prop = boost::get(boost::edge_time_t(), g);
    auto length_prop = boost::get(boost::edge_length_t(), g);
    auto weight_prop = boost::get(boost::edge_weight_t(), g);
    auto visited_prop = boost::get(boost::edge_visited_t(), g);
    auto bidirectional_prop = boost::get(boost::edge_bidirectional_t(), g);

    for(auto i=0u; i<NUM_OF_EDGES;++i)
    {
        uint32_t index_from, index_to, one_direction, time, length;
        f >> index_from >> index_to >> one_direction >> time >> length;

        auto e1 = boost::add_edge(index_from, index_to, g);
        boost::put(time_prop, e1.first, time);
        boost::put(length_prop, e1.first, length);
        boost::put(weight_prop, e1.first, (double)time/length);
        boost::put(visited_prop, e1.first, false);
        
        if (one_direction == 2)
        {
            boost::put(bidirectional_prop, e1.first, true);
            
            auto e2 = boost::add_edge(index_to, index_from, g);
            boost::put(time_prop, e2.first, time);
            boost::put(length_prop, e2.first, length);
            boost::put(weight_prop, e2.first, (double)time/length);
            boost::put(visited_prop, e2.first, false);
            boost::put(bidirectional_prop, e2.first, true);
        }
        else
        {
            boost::put(bidirectional_prop, e1.first, false);
        }
    }

    return result;
}

//////////////////////////////////////////////////////////////////////

Graph g;    

typedef std::vector<Graph::vertex_descriptor> VertexVect;
std::vector<VertexVect> subproblems;

//SubgraphVector Subproblems;

//////////////////////////////////////////////////////////////////////

struct SplitOnSubproblems : boost::default_bfs_visitor
{
    SplitOnSubproblems() 
        : num_vertices(0)
    {}

    mutable uint64_t num_vertices;
    mutable VertexVect vertexVect;

    void finish_vertex(const Graph::vertex_descriptor &s, const Graph &g) const 
    {
        num_vertices++;
        vertexVect.push_back(s);

        if (subproblems.size() < NUM_OF_CARS - 1)
        {   
            if (num_vertices % (NUM_OF_VERTICES / NUM_OF_CARS) == 0 )
            {
                subproblems.push_back(vertexVect);
                vertexVect.clear();
            }
        }
        else
        {
            if (num_vertices == NUM_OF_VERTICES) 
            {
                subproblems.push_back(vertexVect);
            }
        }
    }
};

typedef std::vector<uint32_t> Vect;
typedef std::vector<Vect> Matrix;

uint32_t INF = std::numeric_limits<uint32_t>::max();

void writeMatrix(Matrix &m, uint32_t n)
{
    for(auto i=0u; i<n; ++i)
    {
        for(auto j=0u; j<n; ++j)
        {   
            if (j==0) 
                std::cout << m[i][j];
            else 
                std::cout << ',' << m[i][j];
        }
        std::cout << std::endl;
    }
}

void branchAndBound(Graph * s)
{
    Matrix m;
    auto n = boost::num_vertices(*s);

    std::cout << "Reserve matrix " << n << "x" << n << std::endl;
    m.resize(n);
    for(auto &l : m)
        l.assign(n, INF);

    //init with infinities
    
    auto p = boost::edges(*s);
    auto vertex_index_prop = boost::get(boost::vertex_index_t(), *s);
    auto edge_index_prop = boost::get(boost::edge_index_t(), *s);
    auto edge_time_prop = boost::get(boost::edge_time_t(), *s);
    auto edge_length_prop = boost::get(boost::edge_length_t(), *s);
    for(;p.first!=p.second; p.first++)
    {
        auto source_vertex = boost::source(*p.first, *s); 
        auto target_vertex = boost::target(*p.first, *s);
        
        uint32_t source_index = vertex_index_prop[source_vertex];
        uint32_t target_index = vertex_index_prop[target_vertex];
        uint32_t edge_time = edge_time_prop[*p.first];
        uint32_t edge_length = edge_length_prop[*p.first];
        
        uint32_t weight = (uint32_t)(edge_time/(double)edge_length*10000000);        

        m[source_index][target_index] = weight;
    }

    writeMatrix(m, n);
}


struct Car
{
    Car() : Index(0), TotalTime(0), TotalLength(0)
    {}

    uint32_t Index;
    std::vector<vertex_t> Path;
    uint32_t TotalTime;
    uint32_t TotalLength;
};

size_t greedy(Graph *g)
{
    std::vector<Car> cars;
    
    auto vertices = boost::vertices(*g);
   
    for(auto i=0u; i<INITIAL_VERTEX; ++i) 
        vertices.first++;


    size_t totalLength = 0;
    for(auto i=0u; i<NUM_OF_CARS;++i)
    {
        Car current_car;
        current_car.Index = i;
        
        vertex_t vertex = *vertices.first;
        
        do 
        {
            current_car.Path.push_back(vertex);
        
            auto edges = boost::out_edges(vertex, *g); 
            auto edge_visited_prop = boost::get(boost::edge_visited_t(), *g);
            auto edge_bidirectional_prop = boost::get(boost::edge_bidirectional_t(), *g);
            auto edge_weight_prop = boost::get(boost::edge_weight_t(), *g);
            auto edge_time_prop = boost::get(boost::edge_time_t(), *g);
            auto edge_length_prop = boost::get(boost::edge_length_t(), *g);
            
            // find minimum weight
            auto it = edges.first, it_end=edges.second;
            double min_weight = INF;
            bool min_found = false;
            edge_t min_edge = *it;
            for(;it!=it_end;it++)
            {
                double weight = edge_weight_prop[*it];
                bool visited = edge_visited_prop[*it];
                if ((weight < min_weight) && (visited == false))
                {
                    min_weight = weight;
                    min_found = true;
                    min_edge = *it;
                }
            }
            
            if (min_found)
            { 
                //std::cout << "min_weigth " << min_weight << " time" << edge_time_prop[min_edge] << " length" << edge_length_prop[min_edge] << std::endl;
                uint32_t length = edge_length_prop[min_edge];
                uint32_t time = edge_length_prop[min_edge];
                bool is_bidirectional = edge_bidirectional_prop[min_edge];
              
                // car finished 
                if ((current_car.TotalTime + time) > TIME)
                {
                    break;
                }

                vertex_t new_vertex = boost::target(min_edge, *g);
                current_car.TotalTime += time;
                current_car.TotalLength += length;
                
                boost::put(edge_visited_prop, min_edge, true);
                
                if (is_bidirectional)
                {
                    auto out_edges = boost::out_edges(new_vertex, *g);
                    auto out_it = out_edges.first, out_it_end=out_edges.second;
                    for(;out_it!=out_it_end; out_it++)
                    {
                        auto target_vertex = boost::target(*out_it, *g);
                        if (target_vertex == vertex)
                        {
                            //std::cout << " Reverse direction edge is marked as visited" << std::endl;
                            boost::put(edge_visited_prop, *out_it, true);
                            break;
                        }
                    }
                }

                vertex = new_vertex;
            }
            else 
            {
                uint32_t out_degree = boost::out_degree(vertex, *g);
                auto out_edges = boost::out_edges(vertex, *g);
                auto out_it = out_edges.first, out_it_end=out_edges.second;
                vertex_t target_vertex;
                bool next_vertex_found = false;               
 
                std::uniform_int_distribution<int> uniform_dist(0, out_degree-1);
                int random_vertex = uniform_dist(e1);
                
                for(int i=0;out_it!=out_it_end; out_it++, ++i)
                {
                    if (i == random_vertex)
                    {
                        uint32_t time = edge_length_prop[*out_it];
                        if (current_car.TotalTime + time < TIME)
                        {
                            target_vertex = boost::target(*out_it, *g);
                            uint32_t time = edge_length_prop[*out_it];
                            current_car.TotalTime += time;
                            next_vertex_found = true;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                
                // car finished if no step futher possible
                if (!next_vertex_found)
                    break;

                vertex = target_vertex;    
            }
        }
        while(true);

        std::cout << "Car " << current_car.Index << " finished: TotalLength=" << current_car.TotalLength 
                << " TotalTime=" << current_car.TotalTime << " NumberOfVertices=" << current_car.Path.size() << std::endl;

        totalLength += current_car.TotalLength;

        cars.push_back(current_car);
    }
    std::cout << "Total length  " << totalLength << std::endl; 

    std::ofstream f("path.txt");
    std::vector<std::string> colors = { "0xFF0000", "0x11FF00", "0x1100FF", "0xFFFF00", "0xFF00FF", "0x11FFFF", "0xFFFFFF", "0x108888" };
    int i = 0;
    for(auto &Car : cars)
    {
        f << "Color " << colors[i] << std::endl;
        
        auto longitude_prop = boost::get(boost::vertex_longitude_t(), *g);
        auto latitude_prop = boost::get(boost::vertex_latitude_t(), *g);
        
        for(auto vert : Car.Path)
        {
            double longitude =  longitude_prop[vert];
            double latitude =  latitude_prop[vert];
            f << latitude << " " << longitude << std::endl;
        }        

        ++i;
    }
    return totalLength;
}


int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: \n\t " << argv[0] << " <file_name>" << std::endl;
        return 0;  
    }

    readGraph(argv[1], g);

    //printGraph(g);

    // decomposition

   /* SplitOnSubproblems s;
    boost::breadth_first_search(g, INITIAL_VERTEX, boost::visitor(s));
    
    std::vector<Graph*> subgraphs;
    for(auto & subproblem : subproblems)
    {
        Graph & s = g.create_subgraph();
        for(auto & v : subproblem )
        {
            boost::add_vertex(v, s);
        }
        std::cout << "add subgraph: number of vertices " << boost::num_vertices(s) 
                  << " number of edges " << boost::num_edges(s) << std::endl;
        subgraphs.push_back(&s);
        //TODO: leave only one
        break;
    }
 
    int i = 0;
    for(auto subgraph : subgraphs)
    {
        std::ostringstream file_name;
        file_name << "subproblem_" << ++i << ".txt";

        std::ofstream f(file_name.str());
        auto p = vertices(*subgraph);
        
        // write subproblems to file
        auto longitude_prop = boost::get(boost::vertex_longitude_t(), *subgraph);
        auto latitude_prop = boost::get(boost::vertex_latitude_t(), *subgraph);
        auto originalindex_prop = boost::get(boost::vertex_originalindex_t(), *subgraph);
       
        for(;p.first!=p.second; p.first++)
        {
            double longitude = longitude_prop[*p.first]; 
            double latitude = latitude_prop[*p.first]; 
            uint32_t originalindex = originalindex_prop[*p.first]; 
            f << latitude << " " << longitude << std::endl;
        }
        
        //branchAndBound(subgraph);
    }*/

    //PointVector convexHull = convex_hull(points);

    size_t max = 0;
    for(int i = 0; i<1000; ++i)
    {
        auto res =  greedy(&g);
        
        if(res > max)
            max = res;
    }

    std::cout << " maxmax " << max << std::endl;


    return 0;
}

