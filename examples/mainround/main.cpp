#include <iostream>
#include <fstream>
#include <boost/graph/adjacency_list.hpp>
#include <vector>

typedef boost::adjacency_list<> Graph;

Graph g;
uint64_t NUM_OF_EDGES = 0;
uint64_t NUM_OF_VERTICES = 0;
uint64_t TIME = 0;
uint64_t NUM_OF_CARS = 0;
uint64_t INITIAL_VERTEX = 0;

struct Point
{
    double Lat;
    double Long;
    
    bool operator==(Point const& other)
    {
        return other.Lat == Lat && other.Long == Long; 
    }
};

std::ostream& operator<<(std::ostream& os, Point const& point)
{
    os << "{" << point.Lat << ";" << point.Long << "}";
    return os;
}

typedef std::vector<Point> PointVector; 

PointVector points; 

bool readGraph(const std::string & path)
{
    std::ifstream f(path);
    
    if (!f.is_open())
    {
        std::cout << " Cannot open file " << path << std::endl;
        return false;
    }
    
    f >> NUM_OF_VERTICES >> NUM_OF_EDGES >> TIME >> NUM_OF_CARS >> INITIAL_VERTEX;
    
 
    std::string line; 

    // Coordinates
    for(auto i=0u; i<NUM_OF_VERTICES;++i)
    {
        Point p;
        f >> p.Lat >> p.Long;
        points.push_back(p);
    }    


    std::getline(f, line); 
    for(auto i=0u; i<NUM_OF_EDGES;++i)
    {
        std::getline(f, line); 
    }

    return true;
}

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

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: \n\t " << argv[0] << " <file_name>" << std::endl;
        return 0;  
    }
    
    readGraph(argv[1]);
    
    PointVector convexHull = convex_hull(points);

    return 0;
}

