#include<iostream>
#include<cstdlib>
#include<string>
#define N 4

using namespace std;

struct Song{
    string title;
    int secDuration;
    int likesNum;
};

struct Queue{
    Song playlist[N];
    int head = 0;
    int tail = 0;
    int capacity = 0;
};

bool empty(Queue *queue){
    return queue->capacity==0;
}
int size(Queue *queue){
    return queue->capacity;
}

void pop(Queue *queue){
    if(empty(queue)){
        cout<<"Access denied: queue underflow"<<endl;
    }
    else{
        queue->head = (queue->head + 1)%N;
        queue->capacity--;
    }
}

void push(Queue *queue, Song *song){
    if(size(queue) != N ){
        queue->playlist[queue->tail] = *song;
        queue->tail = (queue->tail + 1)%N;
        queue->capacity++;
    }
    else{
        cout<<"Access denied: queue overflow"<<endl;
    }
}

Song front(Queue *queue){
    return  queue->playlist[queue->head];
}

void print(Queue *queue){
    int n = size(queue);
    Song restore[n];
    Song topEl;
    int i = 0;
    while(empty(queue)!=1){
        topEl = front(queue);
        cout<<topEl.title<<"  "<<topEl.secDuration<<"  "<<topEl.likesNum<<endl;
        restore[i] = front(queue);
        pop(queue);
        i++;
    } 
    for(int i = 0; i<n; i++){
        push(queue,&restore[i]); 
    }
}

int main(){
    Queue playlist;
    Song song;
    Song shuffle1;
    Song shuffle2;

    for(int i=0; i<2; i++){
        cout<<"Add some song into your playlist(title, duration, likes respectively):\n";
        cin>>song.title;
        cin>>song.secDuration;
        cin>>song.likesNum;
        push(&playlist,&song);
    }
    cout<<"The current playlist is: \n";
    print(&playlist);
    cout<<endl;

    for(int i = 0; i<4; i++){
        cout<<"Add some song into your playlist(title, duration, likes respectively):\n";
        cin>>song.title;
        cin>>song.secDuration;
        cin>>song.likesNum;
        push(&playlist,&song);
    }
    cout<<"The current playlist is: \n";
    print(&playlist);
    cout<<endl;

    shuffle1 = front(&playlist);
    pop(&playlist);
    shuffle2 = front(&playlist);
    pop(&playlist);
    push(&playlist,&shuffle2);
    push(&playlist,&shuffle1);
    
    cout<<"The current playlist is: \n";
    print(&playlist);
    cout<<endl;

    shuffle1 = front(&playlist);
    shuffle1.likesNum += 100;
    pop(&playlist);
    push(&playlist,&shuffle1);;
    
    cout<<"The current playlist is: \n";
    print(&playlist);
    cout<<endl;

    pop(&playlist);
    pop(&playlist);
    pop(&playlist);
    pop(&playlist);
    pop(&playlist);

    cout<<"The current playlist is: \n";
    print(&playlist);
    cout<<endl;

    return 0;
}