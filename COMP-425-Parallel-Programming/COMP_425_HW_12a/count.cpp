/*
 * COMP 425 Homework 12A
 * Count Function
 * Guancheng Lai
 */

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;

std::shared_mutex sm;

class locked_ostream
{
    std::ostream& out;
    std::lock_guard<std::mutex> my_lock;
    static std::mutex& out_mutex;

public:
    locked_ostream(std::ostream &out, std::mutex &out_mutex) : out(out), my_lock(out_mutex) {}

    template <typename T>
    void print(const T &value) {
        std::lock_guard lock(out_mutex);
        out << value;
    }

};

template <typename T>
locked_ostream& operator <<(locked_ostream& l_cout, const T& value)
{
    l_cout.print(value);
    return l_cout;

}

class lockable_ostream
{
        locked_ostream get_locked_ostream () {
            return;
        }

};

locked_ostream& operator <<(lockable_ostream& lout, const T&value)
{
    auto locked = lout.get
}


void count(int from, int to)
{
        std::lock_guard loco(sm);
    for (int i = from; i < to; ++i) {
        cout << "Thread " << std::this_thread::get_id() << ": my number is " << i << ".\n";
    }
}

void count_by_three_threads() {
    thread t1(count, 1000, 2000);
    thread t2(count, 2000, 3000);
    thread t3(count, 3000, 4000);

    t1.join();
    t2.join();
    t3.join();
}


int main()
{
    count_by_three_threads();
    return 0;
}
