/*	Using instructions:
		struct node *root = makenode();
		insertword(root, s); */
struct node {
	struct node *ptr[26]; char ch; bool fin;
};

struct node *makenode(char c = '#') {
	struct node *fnode = new node;
	fnode->fin = false;
	fnode->ch = c;
	for(int i = 0; i < 26; i++)
		fnode->ptr[i] = NULL;
	
	return fnode;
};

void insertword(struct node *root, string s) {
	struct node *temp = root;
	for(int i = 0; i < len(s); i++) {
		int id = s[i] - 'a';
		if(temp->ptr[id] == NULL) 
			temp->ptr[id] = makenode(s[i]);
		
		temp = temp->ptr[id];
	} temp->fin = true;
}
