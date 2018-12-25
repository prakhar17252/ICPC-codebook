// Compute the 2D convex hull of a set of points
// Eliminate redundant points from the hull if 
// REMOVE_REDUNDANT is #defined.
// Running time: O(n log n)
// INPUT: a vector of input points, unordered.
// OUTPUT: a vector of points in the convex hull, 
// anticlockwise, starting with bottomleft point
// Returned in the same vector as passed on.

#define REMOVE_REDUNDANT
#define point PT

const ld EPS = 1e-7;

struct PT { 
	int x, y; 
	PT() {} 
	PT(int x, int y) : x(x), y(y) {}
	bool operator < (const PT &p) const { 
		return mp(y,x) < mp(p.y,p.x); }
	bool operator == (const PT &p) const { 
		return fabs(x-p.x)<EPS && fabs(y-p.y)<EPS; }
};

int cross(PT p, PT q){return p.x*q.y-p.y*q.x;}
int area2(PT a, PT b, PT c){ 
	return cross(a,b) + cross(b,c) + cross(c,a); }

#ifdef REMOVE_REDUNDANT
bool bet(const PT &a, const PT &b, const PT &c){
  return (fabs(area2(a,b,c)) < EPS && 
					(a.x-b.x)*(c.x-b.x) <= 0 && 
					(a.y-b.y)*(c.y-b.y) <= 0); }
#endif

void ConvexHull(vector<PT> &pts) {
	sort(all(pts)); onlyunique(pts);
	vector<PT> up, dn;
	for (int i = 0; i < len(pts); i++) {
		while (up.size() > 1 && area2(up[up.size()-2],
						up.back(), pts[i]) >= 0) up.pop_back();
		while (len(dn) > 1 && area2(dn[len(dn)-2],
						dn.back(), pts[i]) <= 0) dn.pop_back();
		up.pb(pts[i]); dn.pb(pts[i]);
	} pts = dn;
	for(int i = len(up)-2; i > 0; i--) pts.pb(up[i]);

	#ifdef REMOVE_REDUNDANT
		if(len(pts) <= 2) return;
		dn.clear(); dn.pb(pts[0]); dn.pb(pts[1]);
		for(int i = 2; i < len(pts); i++) {
			if(bet(dn[len(dn)-2], dn[len(dn)-1], pts[i]))
				dn.pop_back();
			dn.pb(pts[i]);
		}
		if(len(dn) > 2 && bet(dn.back(),dn[0],dn[1])){
			dn[0] = dn.back(); dn.pop_back();
		} pts = dn;
	#endif 
}
