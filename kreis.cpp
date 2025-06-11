#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;


inline double round_to(const double& x, const double& r)
{
  return static_cast<double>(std::round(x / r)) * r;
}

// Dies ist die Main-Funktion
int main (int argc, char* argv []) 
{
  if (argc !=6)
  {
    std::cerr << "Bitte Argumente eingeben!\n";
    std::cerr << "./kreis.exe balgbreite balghoehe anzahlfalten radiusaussen radiusinnen\n";
    std::cerr << "Beispiel:\n";
    std::cerr << "./kreis.exe 37.0 40.0 14 16.0 14.5\n";
    return -1;
  }
  const double cx = std::atof(argv[1])/2.0; // 18.5;
  const double cy = std::atof(argv[2])/2.0; // 20;
  const int N     = std::atoi(argv[3]); // 14
  const double ra = std::atof(argv[4]); // 16;
  const double ri = std::atof(argv[5]); // 14.5;

  auto aussen_p = [&] (double x) { if (abs(x-cx) >= ra) return 0.0; else return cy + sqrt(ra*ra - (x - cx)*(x - cx));} ;
  auto aussen_m = [&] (double x) { if (abs(x-cx) >= ra) return 0.0; else return cy - sqrt(ra*ra - (x - cx)*(x - cx));} ;
  auto innen_p = [&] (double x)  { if (abs(x-cx) >= ri) return 0.0; else return cy + sqrt(ri*ri - (x - cx)*(x - cx));} ;
  auto innen_m = [&] (double x)  { if (abs(x-cx) >= ri) return 0.0; else return cy - sqrt(ri*ri - (x - cx)*(x - cx));} ;


  const double dx = 2*cx / (N-1);
  double x;
  ofstream points("points.dat");
  ofstream cuts("cuts.dat");

  for (int k=0; k<N; ++k)
  {
    x = k*dx;
    double am = round_to(aussen_m(x), 0.05);
    double im = round_to(innen_m(x) , 0.05);
    double ip = round_to(innen_p(x) , 0.05);
    double ap = round_to(aussen_p(x), 0.05);
    points << x << " " << am << " " << im << " " << ip << " " << ap << std::endl;
    cuts << k << " ";
    if (ap == 0)
    {
      cuts << 2*cy << std::endl;
      continue;
    }
    cuts << am << " ";
    if (im == 0) 
    {
      cuts  << ap - am << " " << 2*cy - ap << std::endl;
      continue;
    }
    cuts << im - am << " " << ip - im << " " << ap - ip << " " << 2*cy - ap << std::endl;
  }
  cuts.close();
  points.close();
  std::cout << "Daten wurden in points.dat und cuts.dat geschrieben." << std::endl;
  return 0;
}
