// Solved(☑️) - Clone Graph 
// leetcode link : https://leetcode.com/problems/clone-graph/description/

/* ✔️⭐Approach - 2.2 (using BFS + map(Node*,Node*) orgNodeToCloneNode mapper) - improved version of app-2
         
         explanation :-
              we will apply BFS on the original graph, and build the Clonned graph during this traversal side by side, also we will keep a 'visited' map (to take care of cyclic graphs), also we will be maintaining a 'orgNodeToCloneNode' map to map the original node to the address of clonned nodes corresponding to them, means that when we create a node in clonned graph lets say (1) so we will store its address into this map as value and key as 'original node' , we will first check that if any node is present in our clonned graph with corresponding to 'original node' then use the prv node itself, but if node is not present then create a new node and use that (also store its address into map for key=originalNode). 

       \U0001f50d IMP Note : the prv BFS(app-2) where we mapped 'val' to 'node' will fail in the case where graph has multiple nodes with same values., but if we map 'orgNode' to 'cloneNode' we will not have that issue at all

       \U0001f50d imp note : 
            -> why we need 'orgToCopyNode' map ? 
                    because we do not want to create multiple copies of the same node 
            -> whu we need 'visited' map ? 
                    because what we are dooing here is that we take a org node, create copu of it and attach all the neigh of org node to the corresponding copies of the copy node, now ones a front node is done, we do not want to access it again, so thats why we need a visited node, i.e each org node should enter into the q only ones.

        ✅ T : O(V+E) 
        ✅ S : O(V+E) - visited map, clonedValToNodeAddress map 
   
*/
class Solution {


private:
    // fun.2 : 
    void cloneUsingBFS(Node* src, unordered_map<Node*,bool> &visited, unordered_map<Node*,Node*> &orgNodeToCloneNode){

        // for BFS we need queue 
        queue<Node*> q;
        q.push(src);
        visited[src] = true;

        while(!q.empty()){

            // fetch the org graphs front, and pop it 
            Node* front = q.front();
            q.pop();
            
            vector<Node*> frontNeighbours = front -> neighbors;

            // if there is already a clonned node corresponding to 'front' in clonned graph, then use it, else create a new Clone of front and store it in map 
            Node* frontClone;
            if(orgNodeToCloneNode.find(front) != orgNodeToCloneNode.end()) // already present 
                frontClone = (orgNodeToCloneNode.find(front)) -> second; // .find() returns key-val block's address, so to fetch its value use -> second
            else{  // not present - create new one 
                frontClone = new Node(front -> val);
                orgNodeToCloneNode[front] = frontClone; 
            }

            for(Node* neigh:frontNeighbours){ // explore neighbours of original 'front'

                // if neighClone is present, then use it else create new 'neighClone' and store in map
                Node* neighClone;
                if(orgNodeToCloneNode.find(neigh) != orgNodeToCloneNode.end()) // already present 
                    neighClone = (orgNodeToCloneNode.find(neigh)) -> second;

                else{ // not present - create new node
                    neighClone = new Node(neigh -> val);
                    orgNodeToCloneNode[neigh] = neighClone;
                }

                // connect (or insert) 'neighClone' into adjacency(neighbours) list of cloneFront
                (frontClone -> neighbors).push_back(neighClone);

                // if the 'neigh' node is unvisited, visit it and push it into q
                if(!visited[neigh]){
                    visited[neigh] = true;
                    q.push(neigh);
                }
            } 
        }

    }

public:
    // main func
    Node* cloneGraph(Node* node) {
        
        if(!node) return node;
 
        // step 1 : we need to map 'original node' of nodes to their 'clonned node' (using map), we also need a visited map, 
        unordered_map<Node*,Node*> orgNodeToCloneNode;
        unordered_map<Node*,bool> visited;

        Node* clonnedGraphStartNode = new Node(node -> val);// since we need to return the node with val 1
        orgNodeToCloneNode[node] = clonnedGraphStartNode; 

        // lets create clone graph from original graph's 'node' using BFS 
        cloneUsingBFS(node, visited, orgNodeToCloneNode);

        return clonnedGraphStartNode;
    }
};

//--------------------------------------------------------------------------------------------------------------------------------------------
/* ✔️⭐Approach - 2 (using BFS)
         
         explanation :-
              we will apply BFS on the original graph, and build the Clonned graph during this traversal side by side, also we will keep a visited map (to take care of cyclic graphs), also we will be maintaining a 'clonnedValToNodeAddress' map to map the integer values to the address of nodes of clonned graph, means that when we create a node in clonned graph lets say (1) so we will store its address into this map, and everytime we get a value of 1, we will first check that if any node is present in our clonned graph with value (1) then use the prv node itself, but if node is not present then create a new node and use that (also store its address into map for key=1). 

        ✅ T : O(V+E) 
        ✅ S : O(V+E) - visited map, clonedValToNodeAddress map 
*/

/*
// code
class Solution {
    

private:
    // fun.2 : 
    void cloneUsingBFS(Node* src, unordered_map<Node*,bool> &visited, unordered_map<int,Node*> &clonedValToNodeAddress){

        // for BFS we need queue 
        queue<Node*> q;
        q.push(src);
        visited[src] = true;

        while(!q.empty()){

            // fetch the org graphs front, and pop it 
            Node* front = q.front();
            q.pop();
            
            vector<Node*> frontNeighbours = front -> neighbors;

            // if there is already a clonned node of 'front' in clonned graph, then use it, else create a new Clone of front and store it in map 
            Node* frontClone;
            if(clonedValToNodeAddress.find(front -> val) != clonedValToNodeAddress.end()) // already present 
                frontClone = (clonedValToNodeAddress.find(front -> val)) -> second; // .find() returns key-val block's address, so to fetch its value use -> second
            else{  // not present - create new one 
                frontClone = new Node(front -> val);
                clonedValToNodeAddress[front -> val] = frontClone; 
            }

            for(Node* neigh:frontNeighbours){ // explore neighbours of original 'front'

                // if neighClone is present, then use it else create new 'neighClone' and store in map
                Node* neighClone;
                if(clonedValToNodeAddress.find(neigh -> val) != clonedValToNodeAddress.end()) // already present 
                    neighClone = (clonedValToNodeAddress.find(neigh -> val)) -> second;

                else{ // not present - create new node
                    neighClone = new Node(neigh -> val);
                    clonedValToNodeAddress[neigh -> val] = neighClone;
                }

                // connect (or insert) 'neighClone' into adjacency(neighbours) list of cloneFront
                (frontClone -> neighbors).push_back(neighClone);

                // if the 'neigh' node is unvisited, visit it and push it into q
                if(!visited[neigh]){
                    visited[neigh] = true;
                    q.push(neigh);
                }
            } 
        }

    }

public:
    // main func
    Node* cloneGraph(Node* node) {
        
        if(!node) return node;

        // we need to keep tracks of visited nodes (for cyclic graphs case), also we need to take care that ones a cloned node with data 'x' is created, we do not create node with same data 'x' again, so for that create a mapping between 'value' and 'Node's address' for cloned node 
        unordered_map<Node*,bool> visited;
        unordered_map<int,Node*> valueToClonnedNode; // map

        Node* clonnedGraphStartNode = new Node(1);// since we need to return the node with val 1
        valueToClonnedNode[1] = clonnedGraphStartNode; 

        // lets create clone graph from original graph's 'node' using BFS 
        cloneUsingBFS(node, visited, valueToClonnedNode);

        return clonnedGraphStartNode;
    }
};
*/
