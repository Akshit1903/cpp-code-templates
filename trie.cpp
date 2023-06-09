class Trie {
    class TrieNode{
        public:
        TrieNode* children[26];
        bool isWord;
        TrieNode():isWord(false){
            for(int i=0;i<26;i++){
                children[i]=NULL;
            }
        }
        TrieNode* getChild(char c){
            return children[c-'a'];
        }
        bool doesExist(char c){
            return getChild(c)==NULL;
        }
        void createTrieNode(char c){
            children[c-'a']= new TrieNode();
        }
    };
    TrieNode* root;
    
    
public:

    /** Initialize your data structure here. */
    Trie() {
        root=new TrieNode();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *node=root;
        for(char c:word){
            if(node->doesExist(c)){
                node->createTrieNode(c);
            }
            node=node->getChild(c);
        }
        node->isWord=true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *node=root;
        for(char c:word){
            node=node->getChild(c);
            if(node==NULL){
                return false;
            }
        }
        return node->isWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *node=root;
        for(char c:prefix){
            node=node->getChild(c);
            if(node==NULL){
                return false;
            }
        }
        return true;
    }
};

// extra functions such as startsWith and erase(it deletes nodes as well)

class Trie{
    class TrieNode{
        public:
        TrieNode* children[26];
        int wordCount;
        TrieNode(){
            wordCount=0;
            for(int i=0;i<26;i++){
                children[i]=NULL;
            }
        }
        TrieNode *getChild(char c){
            return children[c-'a'];
        }
        void createNode(char c){
            children[c-'a']=new TrieNode();
        }
        void deleteChildReference(char c){
            children[c-'a']=NULL;
        }
        bool allChildrenNULL(){
            for(int i=0;i<26;i++){
                if(children[i]){
                    return true;
                }
            }
            return false;
        }
    };
    TrieNode *root;
    int getAllWords(TrieNode *node){
        if(node==NULL){
            return 0;
        }
        int res=node->wordCount;
        for(char c='a';c<='z';c++){
            res+=getAllWords(node->getChild(c));
        }
        return res;
    }
    bool eraseWord(TrieNode *node,string word){
        if(word.size()){
            char c=word[0];
            if(node->getChild(c)==NULL || !eraseWord(node->getChild(c),word.substr(1))){
                return false;
            }
            node->deleteChildReference(c);
        }else if(--node->wordCount){
            return false;
        }
        if(node!=root && node->allChildrenNULL()){
            delete node;
            return true;
        }
        return false;
    }
    public:

    Trie(){
        root=new TrieNode();
    }

    void insert(string &word){
        TrieNode *node=root;
        for(char c:word){
            if(node->getChild(c)==NULL){
                node->createNode(c);
            }
            node=node->getChild(c);
        }
        node->wordCount++;
    }

    int countWordsEqualTo(string &word){
        TrieNode *node=root;
        for(char c:word){
            if(node->getChild(c)==NULL){
                return 0;
            }
            node=node->getChild(c);
        }
        return node->wordCount;
    }

    int countWordsStartingWith(string &word){
        TrieNode *node=root;
        for(char c:word){
            if(node->getChild(c)==NULL){
                return 0;
            }
            node=node->getChild(c);
        }
        return getAllWords(node);
    }

    void erase(string &word){
        eraseWord(root,word);
    }
};


// Works with binary numbers, useful in XOR-type questions

class Trie{
    class TrieNode{
        public:
        TrieNode *zero,*one;
        TrieNode() : zero(NULL), one(NULL) {}
		bool isNode(int bit){
			if(bit==0){
				return zero!=NULL;
			}
			return one!=NULL;
		}
        TrieNode* getNode(bool next){
            if(next){
                if(one==NULL){
                    one=new TrieNode();
                }
                return one;
            }
            if(zero==NULL){
                zero=new TrieNode();
            }
            return zero;
        }
    };
    bool isBitSet(int &num,int i){
        return (1<<i) & num;
    }
    public:
    TrieNode *root;
        Trie():root(new TrieNode()) {}

        void insert(int num){
            TrieNode* node=root;
            for(int i=30;i>=0;i--){
                node=node->getNode(isBitSet(num, i));
            }
        }
		int getMaxXOR(int num){
			TrieNode *node=root;
			int res=0;
			for(int i=30;i>=0 && node;i--){
				if(node->isNode(1-isBitSet(num, i))){
					res|=(1<<i);
					node=node->getNode(1-isBitSet(num, i));
				}else if(node->isNode(isBitSet(num, i))){
					node=node->getNode(isBitSet(num, i));
				}
			}
			return res;
		}
};
