#pragma once

#include <thread>

template <class D = void>
class Thread{
    void (*function)(D*);
    D* data;

    bool* doneflag;

    std::thread thread;

    static void RunThread(Thread<D>* thread, D* data){
        printf("Running Thread\n");
        thread->function(data);
        printf("Finished Code\n");
        thread->FinishThread();
        printf("Finished Thread\n");
    }

    void StartThread(){

        /*thread([](Thread* t, D* data){
            t->function(data);
            t->FinishThread();
        }, this, data);*/

        thread = std::thread(&Thread::RunThread, this, data);
        //threadref = thread;
    }

    void FinishThread(){
        if(doneflag != nullptr)
            *doneflag = true;
    }

public:
    Thread(void (*threadLogic)(D*), bool& Finished, D* data){
        this->data = data;
        function = threadLogic;
        doneflag = &(Finished = false);
        StartThread();
    }
    
    Thread(void (*threadLogic)(D*), D* data){
        this->data = data;
        function = threadLogic;
        doneflag = nullptr;
        StartThread();
    }

    ~Thread(){
        //thread.join();
        thread.~thread();
    }
};