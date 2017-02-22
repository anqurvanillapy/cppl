/**
 *  Dinning Philosophers
 *  ====================
 *
 *  Note: This is not the solution, but used for demonstrating deadlocks.
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

#define NUM 5

using namespace std;

int
main(int argc, const char *argv[])
{
    atomic<unsigned> count(0);
    vector<mutex> chops(NUM);
    vector<thread> philosophers(NUM);

    for (unsigned i = 0; i < NUM; ++i) {
        philosophers[i] = thread([&chops, i, &count] {
            for (;;) {
                cout << this_thread::get_id() << " thinking..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                {
                    cout << this_thread::get_id() << " picks left" << endl;
                    lock_guard<mutex> lk_left(chops[i]);
                    {
                        cout << this_thread::get_id() << " picks right" << endl;
                        lock_guard<mutex> lk_right(chops[(i + 1) % NUM]);
                    }
                }
                cout << "times:" << count++ << endl;
            }
        });
    }

    for (auto& p : philosophers) p.join();

    return 0;
}
