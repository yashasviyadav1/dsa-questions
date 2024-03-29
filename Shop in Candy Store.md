# Shop in Candy Store (Greedy)

#### Solved at : [GFG](https://www.geeksforgeeks.org/problems/shop-in-candy-store1145/1)

## ✔️Approach - 1 (Greedy)
```java
class Solution{
    static ArrayList<Integer> candyStore(int candies[],int N,int K){
        
        // Approach-1 (greedy)
        // Time : O(nLogn)
        // Space : O(1)
        
        int i = 0; // next candy to buy
        int j = N-1; // next candy to pick for free
        int minAmount = 0;
        
        // finding minAmount spent
        // we buy the cheapest candy and pick the costlier candy for free
        Arrays.sort(candies);
        while(i <= j){
            minAmount += candies[i++]; // buy cheaper candies
            j = j-K; // took k costlier candies for free
        }
        
        // finding maxAmount spent
        // we buy the costlier candy first and pick cheaper ones for free
        i=N-1;
        j=0;
        int maxAmount = 0;
        while(j <= i){
            maxAmount += candies[i--];// buy costly candy
            j = j + K; // took cheeper candies for free
        }
        
        
        ArrayList<Integer> arr =  new ArrayList<>();
        arr.add(minAmount);
        arr.add(maxAmount);
        return arr;
    }
}

```
