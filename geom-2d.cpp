ld INF = 1e100, EPS = 1e-12, pi = acos(-1);
#define point PT
#define VP vector<PT>

struct PT{ 
	ld x, y; 
	PT() {}
	PT(ld x, ld y) : x(x), y(y) {}
	PT(const PT &p) : x(p.x), y(p.y) {}
	PT operator + (const PT &p) const {
		return PT(x+p.x, y+p.y); }
	PT operator - (const PT &p) const {
		return PT(x-p.x, y-p.y); }
	PT operator * (ld c) const {return PT(x*c, y*c);}
	PT operator / (ld c) const {return PT(x/c, y/c);}
	bool operator == (const PT &p) const {
		return fabs(x-p.x) < EPS && fabs(y-p.y) < EPS;}
	bool operator != (const PT &p) const {
		return fabs(x-p.x) > EPS || fabs(y-p.y) > EPS;}
};
ld dot(PT p, PT q){return p.x*q.x+p.y*q.y;}
ld dist2(PT p, PT q){return dot(p-q,p-q);}
ld dist(PT p, PT q){return sqrtl(dist2(p, q));}
ld cross(PT p, PT q){return p.x*q.y-p.y*q.x;}
ld mag(PT p){return sqrtl(dot(p, p));}
ld to_degree(ld angle){return angle*180.0/pi;}
ld angle_in_radian(PT p, PT q){
	return acos(dot(p, q)/(mag(p)*mag(q)));}
ld angle_in_degree(PT p, PT q){
	 return to_degree(angle_in_radian(p, q));}
ostream &operator<<(ostream &os, const PT &p){ 
    return os<<"("<<p.x<<","<<p.y<< ")";
}
// rotate a pt CCW or CW around the origin
PT RotateCCW90(PT p) { return PT(-p.y,p.x); }
PT RotateCW90(PT p) { return PT(p.y,-p.x); }
PT RotateCCW(PT p, ld t) { return PT(
p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));}
// project pt c onto line through a & b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
  return a+(b-a)*dot(c-a, b-a)/dot(b-a, b-a);}
// project pt c on line segment through a & b
PT ProjectPointSegment(PT a, PT b, PT c){
	ld r = dot(b-a,b-a);
	if(fabs(r) < EPS) return a;
	r = dot(c-a, b-a)/r;
	if(r < 0) return a; if(r > 1) return b;
	return a +(b-a)*r;}
// compute dis from c to segment between a & b
ld DistancePointSegment(PT a, PT b, PT c){
	return dist(c, ProjectPointSegment(a, b, c)); }
//get dis between pt(x,y,z) & plane ax+by+cz=d
ld DistancePointPlane(ld x, ld y, ld z, 
	ld a, ld b, ld c, ld d)
{ return fabs(a*x+b*y+c*z-d)/sqrtl(a*a+b*b+c*c);}
// find if lines from a, b & c, d are parallel
bool LinesParallel(PT a, PT b, PT c, PT d){
	return fabs(cross(b-a, c-d)) < EPS;}
bool LinesCollinear(PT a, PT b, PT c, PT d){
  return LinesParallel(a, b, c, d) && 
	fabs(cross(a-b, a-c)) < EPS && 
	fabs(cross(c-d, c-a)) < EPS;}
// find if line segment from a, b intersects 
// with line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
	if(LinesCollinear(a, b, c, d)){
		if(dist2(a, c) < EPS || 
		dist2(a, d) < EPS || dist2(b, c) < EPS ||
		dist2(b, d) < EPS) return true;
		if(dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 
		&& dot(c-b, d-b) > 0) return false;
		return true;
	}
	if(cross(d-a, b-a)*cross(c-a, b-a) > 0) 
		return false;
	if(cross(a-c, d-c)*cross(b-c, d-c) > 0) 
		return false;
	return true; }
//get intersection of line passing through a,b
//with line passing through c to d, assuming
//unique intersection exists; for segment
//intersection, find if segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d){
    b=b-a; d=c-d; c=c-a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b*cross(c, d)/cross(b, d);}
// compute center of circle given three pts
PT ComputeCircleCenter(PT a, PT b, PT c){
	b=(a+b)/2; c=(a+c)/2; return 
	ComputeLineIntersection(b, b+RotateCW90(a-b),
 	c, c+RotateCW90(a-c));}
// find if pt is in possibly non-convex polygon
// returns 1 for strictly interior pts, 
// 0 for strictly exterior pts
bool PointInPolygon(const VP &p, PT q) {
	bool c = 0;
	for(int i = 0; i < len(p); i++) {
		int j = (i+1)%len(p);
		if((p[i].y <= q.y && q.y < p[j].y || 
		p[j].y <= q.y && q.y < p[i].y) && 
		q.x < p[i].x+(p[j].x-p[i].x)*
		(q.y-p[i].y)/(p[j].y-p[i].y)) c = !c;
	} return c;}
// determine if pt is on boundary of a polygon
bool PointOnPolygon(const VP &p, PT q) {
	for(int i = 0; i < len(p); i++)
		if(dist2(ProjectPointSegment(p[i], 
		p[(i+1)%len(p)], q), q) < EPS) return true;
	return false;}
// find intersection of line through pts a, b
// with circle centered at c with radius r > 0
VP CircleLineIntersection(PT a, PT b, PT c, ld r){
	VP ret; b = b-a; a = a-c;
	ld A = dot(b, b), B = dot(a, b);
	ld C = dot(a, a) - r*r, D = B*B - A*C;
	if(D < -EPS) return ret;
	ret.pb(c+a+b*(-B+sqrt(D+EPS))/A);
	if(D>EPS) ret.pb(c+a+b*(-B-sqrt(D))/A);
	return ret;}
// find intersection of circle at center a with
// radii r with circle at center b with radii R
VP CircleCircleIntersection(PT a,PT b,ld r,ld R){
	VP ret; ld d = sqrt(dist2(a, b));
	if(d > r+R || d+min(r, R) < max(r, R)) 
		return ret;
	ld x =(d*d-R*R+r*r)/(2*d), y = sqrt(r*r-x*x);
	PT v =(b-a)/d; ret.pb(a+v*x+RotateCCW90(v)*y);
	if(y > 0) ret.pb(a+v*x - RotateCCW90(v)*y);
	return ret;}
// This code computes the area or centroid of a
// polygon, assuming that the coordinates are 
// listed in clockwise or anticlockwise fashion
// Note that the centroid is often known as
// the "center of gravity" or "center of mass".
ld ComputeSignedArea(const VP &p) {
	ld area = 0;
	for(int i = 0; i < len(p); i++) {
		int j =(i+1) % len(p);
		area += p[i].x*p[j].y - p[j].x*p[i].y;
	} return area / 2.0;}
ld ComputeArea(const VP &p) {
	return fabs(ComputeSignedArea(p));}
PT ComputeCentroid(const VP &p) {
	PT c(0,0); 
	ld scale = 6.0 * ComputeSignedArea(p);
	for(int i = 0; i < len(p); i++) {
		int j =(i+1) % len(p);
		c+=(p[i]+p[j])*(p[i].x*p[j].y-p[j].x*p[i].y);
	} return c / scale;}
// tests whether or not a given polygon
// (in CW or CCW order) is simple
bool IsSimple(const VP &p) {
for(int i = 0; i < len(p); i++)
	for(int k = i+1; k < len(p); k++) {
		int j =(i+1) % len(p);
		int l =(k+1) % len(p);
		if(i == l || j == k) continue;
		if(SegmentsIntersect(p[i], p[j], p[k], p[l]))
			return false;
		} return true;}
