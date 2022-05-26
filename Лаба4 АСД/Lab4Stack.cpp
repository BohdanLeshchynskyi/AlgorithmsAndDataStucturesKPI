#include<iostream>
#include<cstdlib>
#include<string>
#define N 7

using namespace std;

struct docChange{
    int lineNum;
    string text;
};

struct Stack{
    docChange changeHistory[N];
    int top = -1;
};

void push(Stack *stack, docChange *change){
    if(stack->top+1 >= N){
        cout<<"Access denied: stack overflow!\n";
        return;
    }
    stack->top++;
    stack->changeHistory[stack->top] = *change;  
}

bool empty(Stack *stack){
    return stack->top==-1;
}

void pop(Stack *stack){
    if(stack->top == -1){
        cout<<"Access denied: stack underflow!\n";
        return;
    }
    stack->top--;
}

int size(Stack *stack){
    return stack->top+1;
}

docChange top(Stack *stack){
    return stack->changeHistory[stack->top];
}

void print(Stack *stack){
    int n = size(stack);
    docChange restore[n];
    int i = 0;
    docChange topEl; 
    while(empty(stack)==0){;
        topEl = top(stack);
        cout<<topEl.lineNum<<"  "<<topEl.text<<"\n";
        restore[n - 1 - i] = top(stack);  
        pop(stack);
        i++;
    }
    for(int i = 0; i<n; i++){
        push(stack,&restore[i]); 
    }
}

int main(){
    docChange change;
    docChange textcorr;
    Stack stack;
    for(int i = 0; i<4; i++){
        cout<<"Enter some changes into document(first line number then text changes): \n";
        cin>> change.lineNum;       
        cin>> change.text;
        push(&stack,&change);
    }
    cout<<"The current stack is: \n";
    print(&stack);
    cout<<endl;

    for(int i = 0; i<5; i++){
        cout<<"Enter some changes into document(first line number then text changes): \n";
        cin>> change.lineNum;       
        cin>> change.text;
        push(&stack,&change);
    }
    cout<<"The current stack is: \n";
    print(&stack);
    cout<<endl;

    pop(&stack);
    pop(&stack);
    cout<<"The current stack is: \n";
    print(&stack);
    cout<<endl;


    textcorr = top(&stack);
    pop(&stack);
    cout<<"The current stack is: \n";
    print(&stack);
    cout<<endl;

    cout<<"Enter some text changes into document: \n";       
    cin>> textcorr.text;
    push(&stack,&textcorr);
    cout<<"The current stack is: \n";
    print(&stack);
    cout<<endl;

    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    cout<<"The current stack is: \n";
    print(&stack);
    cout<<endl;

    return 0;
}