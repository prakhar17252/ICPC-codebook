// Minimum enclosing circle, Welzl's algorithm
// Expected linear time.
// If there are duplicate points, remove them first

#define point PT
#define circle CR
struct PT { ld x, y; };
struct CR {
	ld x, y, r;
	CR() {}
	CR(ld x, ld y, ld r): x(x), y(y), r(r) {}
};

CR b_md(vector<PT> R) {
	if(len(R) == 0) return CR(0, 0, -1);
	if(len(R) == 1) return CR(R[0].x, R[0].y, 0);
	if(len(R) == 2) return CR((R[0].x+R[1].x)/2.0,
                              (R[0].y+R[1].y)/2.0,
          hypot(R[0].x-R[1].x, R[0].y-R[1].y)/2.0);
	
  ld D = (R[0].x-R[2].x)*(R[1].y-R[2].y) - 
                  (R[1].x-R[2].x)*(R[0].y-R[2].y);
  
  ld p0 =(((R[0].x-R[2].x)*(R[0].x+R[2].x) + 
          (R[0].y-R[2].y)*(R[0].y+R[2].y))/2 *
          (R[1].y-R[2].y)-((R[1].x-R[2].x) *
          (R[1].x+R[2].x)+(R[1].y-R[2].y) *
          (R[1].y+R[2].y))/2*(R[0].y-R[2].y))/D;

  ld p1 =(((R[1].x-R[2].x)*(R[1].x+R[2].x) +
          (R[1].y-R[2].y)*(R[1].y+R[2].y))/2 *
          (R[0].x-R[2].x)-((R[0].x-R[2].x) *
          (R[0].x+R[2].x)+(R[0].y-R[2].y)*
          (R[0].y+R[2].y))/2*(R[1].x-R[2].x))/D;
  return CR(p0, p1, hypot(R[0].x-p0, R[0].y-p1));
}
CR b_minidisk(vector<PT>& P, int i, vector<PT> R){
	if(i == len(P) || len(R) == 3) return b_md(R);
  CR D = b_minidisk(P, i+1, R);
  if(hypot(P[i].x-D.x, P[i].y-D.y) > D.r) {
    R.push_back(P[i]);
    D = b_minidisk(P, i+1, R);
  } return D;	
}

// Call this function.
CR minidisk(vector<PT> P) {
	shuffle(all(P), rng);
	return b_minidisk(P, 0, vector<PT>());
}
