// Solved(☑️) - Clone Graph 
// leetcode link : https://leetcode.com/problems/clone-graph/description/
/* ✔️⭐Approach - 1.2 (using DFS + map(node*,node*) 'orgNodeToCloneNode' ) - improved version of App-1 
         
         explanation :-
              we will apply DFS on the original graph, and build the Clonned graph during this traversal side by side, also we will keep a 'visited' map (to take care of cyclic graphs), also we will be maintaining a 'orgNodeToCloneNode' map to map the original node to the address of clonned nodes corresponding to them, means that when we create a node in clonned graph lets say (1) so we will store its address into this map as value and key as 'original node' , we will first check that if any node is present in our clonned graph with corresponding to 'original node' then use the prv node itself, but if node is not present then create a new node and use that (also store its address into map for key=originalNode). 

        \U0001f50dVIMP Note : the prv DFS where we mapped 'val' to 'node' will fail in the case where graph has multiple nodes with same values., but if we map 'orgNode' to 'cloneNode' we will not have that issue at all

        ✅ T : O(V+E) 
        ✅ S : O(V+E) - visited map, 'orgNodeToCloneNode' map 
    */


class Solution {
private:
    // fun.2 
    void CloneUsingDFS(Node* src, unordered_map<Node*,bool> &visited, unordered_map<Node*,Node*> &orgNodeToCloneNode){

        visited[src] = true;
        int srcVal = src -> val;
        vector<Node*> neighbours = src -> neighbors;

        // search if a 'cloneNode' corresponding 'orgNode' is present or not, if yes then use it, else create 1 and map this 'clone' with 'org' node
        Node* clonedSrc;
        if(orgNodeToCloneNode.find(src) != orgNodeToCloneNode.end())     
            clonedSrc = (orgNodeToCloneNode.find(src)) -> second;
        else{
            clonedSrc = new Node(srcVal);
            orgNodeToCloneNode[src] = clonedSrc;
        } 

        // explore the neigh of src (org node) and create cloned and connect them
        for(Node* neigh:neighbours){

            Node* clonedNeigh;
            // if there is 'cloneNeigh' maped to key = neigh, then use it, else create 1 and map 'cloneNeigh' with 'neigh' (original)
            if(orgNodeToCloneNode.find(neigh) != orgNodeToCloneNode.end())     
                clonedNeigh = (orgNodeToCloneNode.find(neigh)) -> second;
            else{
                clonedNeigh = new Node(neigh -> val);
                orgNodeToCloneNode[neigh] = clonedNeigh;
            }

            // now connect this 'clonedneigh' with the 'clonedSrc' 
            (clonedSrc -> neighbors).push_back(clonedNeigh);

            // if neigh is not visited, then call DFS for it 
            if(!visited[neigh])
                CloneUsingDFS(neigh,visited,orgNodeToCloneNode);  
        }

    }
public:
    // main func
    Node* cloneGraph(Node* node) {
        if(!node) return node;

        // step 1 : we need to map 'original node' of nodes to their 'clonned node' (using map), we also need a visited map, 
        unordered_map<Node*,Node*> orgNodeToCloneNode;
        unordered_map<Node*,bool> visited;

        // step 2 : now we will create a 'node' which is start of the cloned graph , rest DFS fun will complete the cloned graph
        Node* clonedStartNode = new Node(node -> val);
        orgNodeToCloneNode[node] = clonedStartNode;

        CloneUsingDFS(node, visited, orgNodeToCloneNode);

        return clonedStartNode;
    }



};


//-----------------------------------------------------------------------------------------------------------------------------------

/* ✔️⭐Approach - 1 (using DFS)
         
         explanation :-
              we will apply DFS on the original graph, and build the Clonned graph during this traversal side by side, also we will keep a visited map (to take care of cyclic graphs), also we will be maintaining a 'clonedValToNodeAddress' map to map the integer values to the address of nodes of clonned graph, means that when we create a node in clonned graph lets say (1) so we will store its address into this map, and everytime we get a value of 1, we will first check that if any node is present in our clonned graph with value (1) then use the prv node itself, but if node is not present then create a new node and use that (also store its address into map for key=1). 

        ✅ T : O(V+E) - recursive time
        ✅ S : O(V+E) - visited map, clonedValToNodeAddress map 
*/

/*
// code 
class Solution {
    
private:
    // fun.2 
    void CloneUsingDFS(Node* src, unordered_map<Node*,bool> &visited, unordered_map<int,Node*> &clonedValToNodeAddress){

        visited[src] = true;
        int srcVal = src -> val;
        vector<Node*> neighbours = src -> neighbors;

        // search if a node with val same as 'src' is present in the cloned graph, if yes then store that else create 1 and store it
        // finding 'clonnedsrc' a node with same value as 'src', and using it.
        Node* clonedSrc;
        if(clonedValToNodeAddress.find(srcVal) != clonedValToNodeAddress.end())     
            clonedSrc = (clonedValToNodeAddress.find(src->val)) -> second;
        else{
            clonedSrc = new Node(srcVal);
            clonedValToNodeAddress[srcVal] = clonedSrc;
        } 

        // explore the neigh of src (org node) and create cloned and connect them
        for(Node* neigh:neighbours){

            Node* clonedNeigh;
            // if cloned neigh exist, then ok else create one and store in map
            if(clonedValToNodeAddress.find(neigh -> val) != clonedValToNodeAddress.end())     
                clonedNeigh = (clonedValToNodeAddress.find(neigh -> val)) -> second;
            else{
                clonedNeigh = new Node(neigh -> val);
                clonedValToNodeAddress[neigh -> val] = clonedNeigh;
            }

            // now connect this 'clonedneigh' with the 'clonedSrc' 
            (clonedSrc -> neighbors).push_back(clonedNeigh);

            // if neigh is not visited, then call DFS for it 
            if(!visited[neigh])
                CloneUsingDFS(neigh,visited,clonedValToNodeAddress); 
        }

    }
public:
    // main func
    Node* cloneGraph(Node* node) {
        if(!node) return node;

        // step 1 : we need to map 'values' of nodes to their 'node addresses' (using map), we also need a visited map, 
        unordered_map<int,Node*> clonedValToNodeAddress;
        unordered_map<Node*,bool> visited;

        // step 2 : now we will create a 'node' which is start of the cloned graph , rest DFS fun will complete the cloned graph
        Node* clonedStartNode = new Node(1);
        clonedValToNodeAddress[1] = clonedStartNode;

        CloneUsingDFS(node, visited, clonedValToNodeAddress);

        return clonedStartNode;
    }
};

*/
