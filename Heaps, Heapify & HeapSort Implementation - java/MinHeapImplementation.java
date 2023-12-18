import java.util.*;

// implementation of min Heap 

class MinHeap{ // min heap

    int arr[];
    int size;

    MinHeap(){ // constructor
        arr = new int[99999];
        size = 0;
        arr[0] = -99999;
    }

    void push(int data){// insersion
        size++;
        int index = size;
        arr[index] = data;

        while(index > 1){ // placing newly inserted node at its correct position

            int parentIndex = index/2;
            if(arr[parentIndex] > arr[index]){ // parent > child, swap them both

                int temp = arr[parentIndex]; // swap values
                arr[parentIndex] = arr[index];
                arr[index] = temp;

                index = parentIndex; //update the childs index, coz it has shifted to above now 
            }
            else return; // node placed at its correct position
        }
    }

    void pop(){

        int deletedElement = arr[1]; 
        arr[1] = arr[size];
        size--;
        int index = 1 ; // lets place this top element at its coorect position
        System.out.println("popped " + deletedElement + " from top");

        while(index < size){

            int leftChildIndex = 2*index;
            int rightChildIndex = 2*index + 1;

            // in min heap smallest value is on top
            int smallestChildIndex = index;

            if(leftChildIndex <= size && arr[leftChildIndex] < arr[index])
                smallestChildIndex = leftChildIndex;

            if(rightChildIndex <= size && arr[rightChildIndex] < arr[smallestChildIndex])
                smallestChildIndex = rightChildIndex;
            
            // if we found that at least 1 child has smaller value then swap
            if(smallestChildIndex != index){ // swap parent and smaller child
                int temp = arr[index]; // swap values
                arr[index] = arr[smallestChildIndex];
                arr[smallestChildIndex] = temp;

                index = smallestChildIndex;// updated index of parent
            }
            else break;//node placed at its correct position

            // System.out.println("index " + index + " is " + arr[index] + " and size of heap : " + size);
        }

    }

    void print(){
        if(size == 0){
            System.out.println("Can't print empty heap");
        }

        for(int i=1; i <= size; i++)
            System.out.print(arr[i] + " ");
        System.out.println();
    }

    
}


class MinHeapImplementation{

    public static void main(String ... args){
        
        MinHeap minHp = new MinHeap();
        /*  min heap
                 2
               /  \
              8   10
             / \
            20  9
         */

        minHp.push(10);        
        minHp.push(20);
        minHp.push(8);
        minHp.push(9);       
        minHp.push(2);

        System.out.print("min Heap : ");
        minHp.print();

        // minHp.pop();        
        minHp.pop();
        
        System.out.print("min Heap : ");
        minHp.print();
        
        /*  min heap
                 8
               /  \
              9   10
             / 
            20  
         */

        minHp.pop();
        System.out.print("min Heap : ");
        minHp.print();

        /*  min heap
                 9
               /  \
              20  10

              9, 20, 10
         */


        minHp.pop();
        System.out.print("min Heap : ");
        minHp.print();

        
        minHp.pop();
        System.out.print("min Heap : ");
        minHp.print();

        
        minHp.pop();
        System.out.print("min Heap : ");
        minHp.print();




    }
}