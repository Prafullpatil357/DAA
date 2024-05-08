#include<iostream>
using namespace std;
int main(){
int i,n;
int a[9];     // Declaring an integer array 'a' of size 9
cout<<"Enter the elements in array :"<<endl; 
for(i=0; i<9; i++){
cin>>a[i];                                       // Taking input for each element of the array from the user
}
int low = 0;
int high = 9-1;
int mid = (low+high)/2;                      // Calculating the middle index of the array
cout<<"Enter the element to be searched:"; cin>>n;
for(i=0; i<9; i++){
if (n == mid) {                      // Checking if the element to be searched is equal to the middle element 
cout<<"Element found !";
break;           // Exiting the loop
}
if(n > mid) {
low = mid+1;  }
if (n < mid) {
high = mid-1;  }
mid = (low+high)/2;             // Calculating the new middle index
}
if(i == 9)
cout<<"\nElement not found!";               // Displaying a message indicating element not found
return 0;                                                 // Indicating successful completion of the program
}

/* Output:-
Enter the elements in array :
21 
12
4
54
32
67
87
14
90
Enter the element to be searched:4
Element found !
*/
 109 changes: 109 additions & 0 deletions109  
DFS.cpp
@@ -0,0 +1,109 @@
#include<iostream>
#include<stdlib.h> 					// Include this header for using exit()
using namespace std;

#define MAX 100
#define initial 1
#define visited 2

int n;
int adj[MAX][MAX];
int state[MAX];
void DF_traversal();
void DFS(int v);
void create_graph();
int stack[MAX];
int top = -1;

void push(int v);
int pop();
int isEmpty_stack();

int main() {
    create_graph();
    DF_traversal();
    return 0; 						// This is where the main function should end
}
void DF_traversal() {
    int v;
    for(v = 0; v < n; v++)
        state[v] = initial;
    cout << "Enter starting node for Depth first search: ";
    cin >> v;
    DFS(v);  }
void DFS(int v) {
    int i;
    push(v);
    while(!isEmpty_stack()) {
        v = pop();
        if (state[v] == initial) {
            cout << v << " "; 							// Print visited node
            state[v] = visited; }
        for(i = n - 1; i >= 0; i--) {
            if (adj[v][i] == 1 && state[i] == initial)
                push(i); }
    }
}
void push(int v) {
    if (top == (MAX - 1)) {
        cout << "\nStack overflow";
        return;
    }
    top = top + 1;
    stack[top] = v;
}
int pop() {
    int v;
    if (top == -1) {
        cout << "\nStack underflow";
        exit(1); 						// Exit the program if underflow occurs
    }
    else {
        v = stack[top];
        top = top - 1;
        return v;   }
}
int isEmpty_stack() { 
    if (top == -1)
        return 1;						 // Return 1 if the stack is empty
    else
        return 0;  }
void create_graph() {
    int i, max_edges, origin, destin; 
    cout << "Enter the number of nodes: "; 
    cin >> n;
    max_edges = n * (n - 1); 				// Calculate maximum possible edges
    for(i = 0; i < max_edges; i++) {
        cout << "Enter the edge " << i << " (or -1 -1 to stop): ";
        cin >> origin >> destin;
        if((origin == -1) && (destin == -1))
            break;
        if (origin >= n || destin >= n || origin < 0 || destin < 0) {
            cout << "Invalid edge !\n";
            i--; 							// Decrement i to re-enter edge
        }
        else {
            adj[origin][destin] = 1; // Mark the edge }
    }
}
}

/*
Output:-
Enter the edge 0 (or -1 -1 to stop): 0  1
Enter the edge 1 (or -1 -1 to stop): 1  2
Enter the edge 2 (or -1 -1 to stop): 1  3
Enter the edge 3 (or -1 -1 to stop): 3  1
Enter the edge 4 (or -1 -1 to stop): 3  3
Enter the edge 5 (or -1 -1 to stop): 3  2
Enter the edge 6 (or -1 -1 to stop): 2  2
Enter the edge 7 (or -1 -1 to stop): 2  3
Enter the edge 8 (or -1 -1 to stop): 2  1
Enter the edge 9 (or -1 -1 to stop): 1  1
Enter the edge 10 (or -1 -1 to stop): 1  0
Enter the edge 11 (or -1 -1 to stop): 2  0
Enter starting node for Depth first search: 0
0 1 2 3
*/
 173 changes: 173 additions & 0 deletions173  
Dijikstras.cpp
@@ -0,0 +1,173 @@
#include <iostream>
using namespace std;

#define MAX 100
#define TEMP 0
#define PERM 1
#define infinity 9999
#define NIL -1

void findPath(int s, int v);                 // function declaration to find the shortest path
void Dijkstra(int s);                          // function declaration for Dijkstra's algorithm
int min_temp();
void create_graph();

int n; // number of vertices
int adj[MAX][MAX];                       // adjacency matrix to represent the graph
int pred[MAX];                                // array to store predecessors in the shortest path 
int pathlength[MAX];
int status[MAX];

int main() {
    int s, v;                                            // variables for source and destination vertices 

    create_graph();
    cout << "Enter the source vertex: ";
    cin >> s;
    Dijkstra(s);                                      // calling Dijkstra's algorithm to find shortest paths 

                                                            // start of while loop
    while (1) {
        cout << "Enter destination vertex (-1 to quit): ";
        cin >> v;                                   // taking input for destination vertex 

        if (v == -1)
            break;
        if (v < 0 || v >= n)                         // if the input vertex is out of range, display error message
            cout << "This vertex does not exist\n";
        else if (v == s)
            cout << "Source and destination vertices are the same\n";
        else if (pathlength[v] == infinity)
            cout << "There is no path from source to destination vertex\n";
        else                                          // if a valid destination vertex is entered, find and display the shortest path 
            findPath(s, v);
    }
    // end of while loop

    return 0;
} // end of main section

void Dijkstra(int s) {
    int i, current;

                                                                                                         // make all vertices temporary
    for (i = 0; i < n; i++) {
        pred[i] = NIL;
        pathlength[i] = infinity;
        status[i] = TEMP;
    }

                                                                                                      // make pathlength of source vertex = 0
    pathlength[s] = 0;

                                                                                                    // start of while loop
    while (1) {
                                    // search for temporary vertex for minimum pathlength and make it 'current' vertex
         current = min_temp();

        if (current == NIL)
            return;
        status[current] = PERM;

        for (i = 0; i < n; i++) {
                                                                                                           // check for adjacent temporary vertices
            if ((adj[current][i] != 0) && (status[i] == TEMP))
                if (pathlength[current] + adj[current][i] < pathlength[i]) {
                    pred[i] = current; // relabel it
                    pathlength[i] = pathlength[current] + adj[current][i];
                }
        }
    }
}                                                                                                                // end of Dijkstra function

/* returns temporary vertex with minimum value of pathlength, returns NIL if no temporary vertex left or all temporary vertices left have pathlength infinity */
int min_temp() {
    int i;
    int min = infinity;
    int k = NIL;
    for (i = 0; i < n; i++) {
        if (status[i] == TEMP && pathlength[i] < min) {
            min = pathlength[i];
            k = i;
        }
    }
    return k;
}                                                                                                                  // end of min_temp

void findPath(int s, int v) {
    int i, u;
    int path[MAX]; // stores the shortest path
    int shortDist = 0; // length of shortest path
    int count = 0; // number of vertices in the shortest path

                                                                                                                    // store the full path in the array path
    while (v != s) {
        count++;
        path[count] = v;
        u = pred[v];
        shortDist += adj[u][v];
        v = u;
    }
    count++;
    path[count] = s;

    cout << "Shortest path is: ";
    for (i = count; i >= 1; i--)
        cout << path[i] << " ";
    cout << "\nThe shortest distance is: " << shortDist << endl;
}                                                                                                                              // end of findPath

void create_graph() {
    int i, max_edges, origin, destin, wt;
    cout << "Enter the number of vertices: ";
    cin >> n;

    max_edges = n * (n - 1);

    for (i = 1; i <= max_edges; i++) {
        cout << "Enter edge " << i << " (enter -1 -1 to finish): ";
        cin >> origin >> destin;

        if (origin == -1 && destin == -1)
            break;

        cout << "Enter weight of this edge: ";
        cin >> wt;

        if (origin > n || destin > n || origin < 0 || destin < 0) {
            cout << "Invalid edge! Please enter again." << endl;
            i--;
        } else
            adj[origin][destin] = wt;                             // assigning weight to the edge in the adjacency matrix 
    }  
}


/* Output:-
Enter the number of vertices: 3
Enter edge 1 (enter -1 -1 to finish): 0 1
Enter weight of this edge: 2
Enter edge 2 (enter -1 -1 to finish): 1 0
Enter weight of this edge: 4
Enter edge 3 (enter -1 -1 to finish): 1 2
Enter weight of this edge: 5
Enter edge 4 (enter -1 -1 to finish): 2 1
Enter weight of this edge:  6
Enter edge 5 (enter -1 -1 to finish): 0 2
Enter weight of this edge: 3
Enter edge 6 (enter -1 -1 to finish): 2 0
Enter weight of this edge: 7
Enter the source vertex: 0
Enter destination vertex (-1 to quit): 2
Shortest path is: 0 2
The shortest distance is: 3
Enter destination vertex (-1 to quit): 1
Shortest path is: 0 1
The shortest distance is: 2
Enter destination vertex (-1 to quit): 0
Source and destination vertices are the same
Enter destination vertex (-1 to quit): 3
This vertex does not exist
Enter destination vertex (-1 to quit):
*/
 73 changes: 73 additions & 0 deletions73  
Merge.cpp
@@ -0,0 +1,73 @@
#include<iostream>
using namespace std;
#define max 100                                                                 // Macro definition for maximum size of array  

void merge_sort(int arr[],int low,int up);
void merge_s(int arr[],int temp[],int low1,int up1,int low2,int up2);
void copy_s(int arr[],int temp[],int low,int up);
int main()
{
 int i,n,arr[max];
 cout<<"enter the size of array:"<<endl;
 cin>>n;
 cout<<"enter array elements "<<endl;
 for(i=0;i<n;i++)
 {
 cin>>arr[i];
 }
 merge_sort(arr,0,n-1);                                                       // Sorting array using merge sort
 cout<<"sorted list is "<<endl;
 for(i=0;i<n;i++)
 cout<<arr[i]<<" ";
  return 0;
  }
  void merge_sort(int arr[],int low,int up)                           // Merge sort function
  {
   int mid;
   int temp[max];                                                               // Temporary array for merging
   if(low<up)
   {
   mid=(low+up)/2;
   merge_sort(arr,low,mid); //left sublist                          // Recursive calls to divide array into sublists
   merge_sort(arr,mid+1,up); //right sublist
   merge_s(arr,temp,low,mid,mid+1,up);
   copy_s(arr,temp,low,up);                                              // Copying the merged sublist back to original array
   } 
  }
  void merge_s(int arr[],int temp[],int low1,int up1,int low2,int up2)
  {
   int i=low1;
   int j=low2;
   int k=low1;
   while((i<=up1)&&(j<=up2))                                     // Merging the sublists
   {
   if(arr[i]<=arr[j])
     temp[k++]=arr[i++];
      else
      temp[k++]=arr[j++];
      }
      while(i<=up1)                                                   // Copying remaining elements of left sublist if any
      temp[k++]=arr[i++];
      while(j<=up2)
      temp[k++]=arr[j++];
     }
     void copy_s(int arr[],int temp[],int low,int up)     
               // Function to copy elements from temporary array to original array
     { 
      int i;
      for(i=low;i<=up;i++)                           // Copying elements from temp array to original array 
      arr[i]=temp[i];
     }

/* Output:-
enter the size of array:
5
enter array elements 
34   
1
23
6
5
sorted list is 
1 5 6 23 34 
*/
 76 changes: 76 additions & 0 deletions76  
Quick.cpp
@@ -0,0 +1,76 @@
#include<iostream>
using namespace std;
void quick(int a[], int l, int up);                       // Function to perform quick sort.
int partition(int a[], int l, int up);                    // Function to partition the array.
int main() 
{ 
 int n;
 cout<<"enter the size of an array"<<endl;             // Prompting user to enter the size of the array.
 cin>>n;
 int arr[n];
 cout<<"enter array elements"<<endl;
 for(int i=0;i<n;i++)
 {
 cin>>arr[i];               // Reading array elements from the user.
 }

 int low = 0;
 int up = n-1;
 quick(arr, low, up);                                                // Calling quick sort function to sort the array.
 cout << "sorted elements are" << endl;
  for (int i = 0; i <= up; i++) {
   cout << arr[i] << " ";                                           // Printing sorted elements
   }
   cout << endl;
   return 0;
  }
  void quick(int a[], int l, int up) {
   if (l >= up) {
   return;
   }
   int pvtloc = partition(a, l, up);                          // Partitioning the array and obtaining pivot location.
   quick(a, l, pvtloc - 1); //left sublist
   quick(a, pvtloc + 1, up); //right sublist
  }
  int partition(int a[], int l, int up) {
   if (l >= up) {
   return l;
   }
   int temp, pvt;
   int i = l + 1;
   int j = up;
   pvt = a[l];
   while (i <= j) {
     while (a[i] < pvt) {
      i++;                                      // Moving towards right until element greater than or equal to pivot is found.
      }
      while (a[j] > pvt) {
      j--;
      }
      if (i < j) {
      temp = a[i];
      a[i] = a[j];
      a[j] = temp;                                                // Swapping elements if they are out of place.
      i++;
      j--;
      } else {
      i++;
      }
      }
      // Swap pivot with element at position j
      temp = a[l];
      a[l] = a[j];
      a[j] = temp;                                                  // Placing pivot at its correct position.
      return j;
     }


/* Output:-
   enter the size of an array
    5
   enter array elements
   5 4 3 2 1
   sorted elements are
   1 2 3 4 5
   */
 96 changes: 96 additions & 0 deletions96  
Strassen.cpp
@@ -0,0 +1,96 @@
#include<iostream>
using namespace std;

int main(){
  int a[2][2], b[2][2], c[2][2] , i ,j;
  int m1,m2,m3,m4,m5,m6,m7;

  cout<<"Enter the four elements of a matrix :"<<endl;

  for(i=0 ; i<2 ; i++){
    for(j=0;j<2;j++){
        cin>>a[i][j];
    }
  }

  cout<<"Enter the four elements of b matrix :"<<endl;

  for(i=0 ; i<2 ; i++){
    for(j=0;j<2;j++){
        cin>>b[i][j];
    }
  }

  cout<<"The a matrix is :"<<endl;

  for(i=0 ; i<2 ; i++){
        cout<<endl;
    for(j=0;j<2;j++){
        cout<<a[i][j]<<" ";
    }
  }

  cout<<endl;

  cout<<"The b matrix is :"<<endl;

  for(i=0 ; i<2 ; i++){
        cout<<endl;
    for(j=0;j<2;j++){
        cout<<b[i][j]<<" ";
    }
  }

  cout<<endl; 
						  // Strassen's Algorithm Multiplication
  m1 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
  m2 = (a[1][0] + a[1][1]) * b[0][0];
  m3 = a[0][0] * (b[0][1] - b[1][1]);
  m4 = a[1][1] * (b[1][0] - b[0][0]);
  m5 = (a[0][0] + a[0][1]) * b[1][1];
  m6 = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
  m7 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);
							// Calculate the result matrix
  c[0][0] = m1 + m4 - m5 + m7;
  c[0][1] = m3 + m5;
  c[1][0] = m2 + m4;
  c[1][1] = m1 - m2 + m3 + m6;

  cout<<"After multiplication using Strassen's Algorithm\n";

  for(i =0 ; i<2 ; i++){
    cout<<endl;
    for(j=0; j<2 ; j++){
        cout<<c[i][j]<<" ";
    }
  }

  return 0;

}

/*Output:-
Enter the four elements of a matrix :
2
4
6
8
Enter the four elements of b matrix :
1
3
5
7
The a matrix is :
2 4
6 8
The b matrix is :
1 3
5 7
After multiplication using Strassen's Algorithm
22 34
46 74
*/
 89 changes: 89 additions & 0 deletions89  
knapsack.cpp
@@ -0,0 +1,89 @@
#include<iostream>
using namespace std;
void knapsack(int n,float weight[],float profit[],float capacity)               // Function to solve knapsack problem 
{
  float x[20],tp=0;
  int i,j,u;
  u=capacity;
  for(i=0;i<n;i++)                                                                                    // Initialize result vector
   x[i]=0.0;
   for(i=0;i<n;i++)                                                                                    // Greedy approach to fill knapsack 
   {
     if(weight[i]>u)
     break;
     else
     {
     x[i]=1.0;
     tp=tp+profit[i];
     u=u-weight[i];
     }
   }

   if(i<n)                                                                                      // If there's still capacity left, fill it partially 
     x[i]=u/weight[i];
     tp=tp+(x[i]*profit[i]);
     cout<<("\n The result vector is: ");

     for(i=0;i<n;i++)
     cout<<"\t"<<x[i];
     cout<<"\n Maximum profit is: "<<tp;
     }

int main()
{
float weight[20],profit[20],capacity;
int num,i,j;
float ratio[20],temp;
cout<<"\n Enter the number of objects:  ";
cin>>num;                                                                                       // Output result vector and maximum profit
cout<<"\n Enter the weights and profit of each objects:  ";

for(i=0;i<num;i++)
{
   cin>>weight[i]>>profit[i];
}                                                                                                              // Input capacity of knapsack
cout<<"\n Enter the capacity of knapsack:  ";
cin>>capacity;

 for(i=0;i<num;i++)
  {
    ratio[i]=profit[i]/weight[i];
  }

  for(i=0;i<num;i++)
  {
    for(j=i+1;j<num;j++)
    {
      if(ratio[i]<ratio[j])
      {
         temp=ratio[j];
         ratio[j]=ratio[i];
         ratio[i]=temp;

         temp=weight[j];
         weight[j]=weight[i];
         weight[i]=temp;

         temp=profit[j];
         profit[j]=profit[i];
         profit[i]=temp;
       }
    }
  }
                                                                                   // Call knapsack function to solve the problem
  knapsack(num,weight,profit,capacity);
  return(0);
}

 /*Output:-
 Enter the number of objects:  3
 Enter the weights and profit of each objects:  7 12
   8 11
   6 14
 Enter the capacity of knapsack:  15
 The result vector is:  1       1       0.25
 Maximum profit is: 28.75
 */
