// Node* root = new Node('\0'); : initialisation
// insert(s, root); : insert word
struct Node {
  char ch; bool fin; Node* ptr[26];

  Node(char ch = '\0') : ch(ch), fin(false) {
    for (int i = 0; i < 26; i++) ptr[i] = nullptr;}
};

void insert(string s, Node* root) {
  Node* temp = root;
  for(char &ch : s) {
    if(temp->ptr[ch - 'a'] == nullptr)
    { temp->ptr[ch - 'a'] = new Node(ch); }
    temp = temp->ptr[ch - 'a'];
  } temp->fin = true; }
