
#ifndef _SERVICE_QUEUE_H
#define _SERVICE_QUEUE_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ServiceQueue {

  private:
        /** Your private data members here!
        *   (you should have NO PUBLIC data members!
        *
        * Nested private types also go here.
        * For example, if your design needs some kind of
        *   structure, you would specify it here.
        */

    //int line;
    //ServiceQueue *next;
    //ServiceQueue *prev;

    //vector<ServiceQueue *> buzzer;
    //vector<ServiceQueue *> que;

    struct node{
        int data;
        node *next;
        node *prev;
        node(int a): data(a), next(nullptr), prev(nullptr){};
    };

    node *head;
    node *tail;
    node *del;

    vector<node *> buzzers;
    vector<node *> que;

  public:

	/**
	 * Constructor
	 * Description: intializes an empty service queue.
	 *
	 * RUNTIME REQUIREMENT: O(1)
	 *
         * TODO
	 */
/*         ServiceQueue() {
            next = nullptr;
            prev = nullptr;
         }

         ServiceQueue(int a){
            int line = a;
            next = nullptr;
            if (que.size()!=0)
                prev = que.at(a-1);
            else
                prev = nullptr;
         }
*/

    ServiceQueue() {
            head = nullptr;
            tail = nullptr;
         }


	/**
	 * Destructor
	 * Description:  deallocates all memory assciated
	 *   with service queue
	 *
	 * RUNTIME REQUIREMENT:  O(N_b) where N_b is the number of buzzer
	 *	IDs that have been used during the lifetime of the
	 *	service queue; in general, at any particular instant
	 *	the actual queue length may be less than N_b.
	 *
	 *	[See discussion of "re-using buzzers" below]
	 *
         * TODO
	 */
/*	~ServiceQueue() {
            delete next;
            delete prev;
        }
*/
       /* void addNode(int num){ // add a new node
            if(head==nullptr && tail==nullptr){
                head = new node(num);
                tail = head;
            }

            else{
                node *newNode = new node(num);
            }
         }
*/

    ~ServiceQueue() {
        delete head;
        delete tail;
        }


	/**
	 * Function: snapshot()
         * param:  buzzers is an integer vector passed by ref
	 * Description:  populates buzzers vector with a "snapshot"
         *               of the queue as a sequence of buzzer IDs
         *
	 *
	 * RUNTIME REQUIREMENT:  O(N)  (where N is the current queue
	 *		length).
	 */
	void snapshot(std::vector<int> &buzzers) {
             buzzers.clear();


             // TODO
             vector<int> number_elements;
             for(int i = 0; i<que.size(); i++){
                number_elements.push_back(que.at(i)->data);
             }
             buzzers = number_elements;
        }

	/**
	 * Function: length()
	 * Description:  returns the current number of
	 *    entries in the queue.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	int  length() {

             return que.size();   // placeholder

        }

	/**
	 * Function: give_buzzer()
         * Return:   buzzer-ID (integer) assigned to the new customer.
	 * Description:  This is the "enqueue" operation.  For us
	 *    a "buzzer" is represented by an integer (starting
	 *    from zero).  The function selects an available buzzer
	 *    and places a new entry at the end of the service queue
	 *    with the selected buzer-ID.
	 *    This buzzer ID is returned.
	 *    The assigned buzzer-ID is a non-negative integer
	 *    with the following properties:
	 *
	 *       (1) the buzzer (really it's ID) is not currently
	 *         taken -- i.e., not in the queue.  (It
	 *         may have been in the queue at some previous
	 *         time -- i.e., buzzer can be re-used).
	 *	  This makes sense:  you can't give the same
	 *	  buzzer to two people!
	 *
	 *       (2) Reusable Buzzers:  A re-usable buzzer is
	 *	  a buzzer that _was_ in the queue at some previous
	 *	  time, but currently is not.
	 *
         *         REQUIREMENT:  If there is one or more reusable
         *         buzzer, you MUST return one of them; furthermore,
         *         it must be the buzzer that became reusable most
         *         MOST RECENTLY.
	 *
	 *       (3) if there are no previously-used / reusable buzzers,
         *         the SMALLEST possible buzzer-ID is used (retrieved from
         *         inventory).
	 *	    Properties in this situation (where N is the current
	 *	      queue length):
	 *
	 *		- The largest buzzer-ID used so far is N-1
	 *
	 *		- All buzzer-IDs in {0..N-1} are in the queue
	 *			(in some order).
	 *
	 *		- The next buzzer-ID (from the basement) is N.
	 *
	 *    In other words, you can always get more buzzers (from
	 *    the basement or something), but you don't fetch an
	 *    additional buzzer unless you have to (i.e., no reusable buzzers).
	 *
	 * Comments/Reminders:
	 *
	 *	Rule (3) implies that when we start from an empty queue,
	 *	the first buzzer-ID will be 0 (zero).
	 *
	 *	Rule (2) does NOT require that the _minimum_ reuseable
	 *	buzzer-ID be used.  If there are multiple reuseable buzzers,
	 *	any one of them will do.
	 *
	 *	Note the following property:  if there are no re-useable
	 *	buzzers, the queue contains all buzzers in {0..N-1} where
	 *       N is the current queue length (of course, the buzzer IDs
	 *	may be in any order.)
	 *
	 * RUNTIME REQUIREMENT:  O(1)  ON AVERAGE or "AMORTIZED"
	 *          In other words, if there have been M calls to
	 *		give_buzzer, the total time taken for those
	 *		M calls is O(M).
	 *
	 *		An individual call may therefore not be O(1) so long
	 *		as when taken as a whole they average constant time.
	 *
	 */
	int  give_buzzer() {
        int b;
        if(buzzers.size()!=0){
           b = buzzers.back()->data;
           buzzers.pop_back();

        }
        else{
            b = que.size();
        }


        if (que.size()!=0){             // when size is more than 0
            que.push_back(new node(b)); // create a node
            int temp = que.at(b)->data;
            tail = que.at(b);           // set-up the tail
            //cout << temp << endl;     // debug

            que.at(temp)->prev = que.at(temp-1);  // linking current to previous node
            que.at(temp-1)->next = que.at(temp);  // linking previous to current node
        }

        if(que.size()==0){
            que.push_back(new node(b)); // create a node
            int temp = que.at(b)->data;
            head = que.at(b);           // set-up the head

            //cout << temp << endl;     // debug
        }

        //cout << que.at(b)->data << endl;   debug


        //que.push_back(new ServiceQueue(b));  debug
        //cout << que.at(b)->line << endl;
        return b;  // placeholder
    }

	/**
	 * function: seat()
	 * description:  if the queue is non-empty, it removes the first
	 *	 entry from (front of queue) and returns the
	 *	 buzzer ID.
	 *	 Note that the returned buzzer can now be re-used.
	 *
	 *	 If the queue is empty (nobody to seat), -1 is returned to
	 *	 indicate this fact.
         *
         * Returns:  buzzer ID of dequeued customer, or -1 if queue is empty.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	int seat() {

        if(que.size()==0)
           return -1;  // placeholder

        else{
            int temp = que.front()->data;           // take the data number
            //head->next = nullptr;            // delink next
            //head->next->prev = nullptr;      // delink prev from current
            //del = head;
            //head = head->next;

            del = que.front();
            que.front() = que.front()->next;

            que.erase(que.begin());                     // remove the node

            buzzers.push_back(new node(temp));       // add the number to bucket
            return temp;
        }

        }


	/**
	 * function: kick_out()
	 *
	 * description:  Some times buzzer holders cause trouble and
	 *		a bouncer needs to take back their buzzer and
	 *		tell them to get lost.
	 *
	 *		Specifially:
	 *
	 *		If the buzzer given by the 2nd parameter is
	 *		in the queue, the buzzer is removed (and the
	 *		buzzer can now be re-used) and 1 (one) is
	 *		returned (indicating success).
	 *
	 * Return:  If the buzzer isn't actually currently in the
	 *		queue, the queue is unchanged and false is returned
	 *		(indicating failure).  Otherwise, true is returned.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	bool kick_out(int buzzer) {
        if (que.at(buzzer)->data!=buzzer)
           return false;  // placeholder
        else{
            que.at(buzzer)->prev->next = que.at(buzzer)->next;
            que.at(buzzer)->next->prev = que.at(buzzer)->prev;

            que.at(buzzer)->next = nullptr;
            que.at(buzzer)->prev = nullptr;

            del = que.at(buzzer);
            delete del;

            buzzers.push_back(new node(buzzer));       // add the number to bucket
            kickThis(buzzer);
            return true;
        }

        }

        void kickThis(int buzzer){                 // debug function // unfinished
            for(int i=0; i<que.size(); i++){
                if(que.at(i)->data == buzzer)
                    que.erase(que.begin()+i);
            }

        }

	/**
	 * function:  take_bribe()
	 * description:  some people just don't think the rules of everyday
	 *		life apply to them!  They always want to be at
	 *		the front of the line and don't mind bribing
	 *		a bouncer to get there.
	 *
	 *	        In terms of the function:
	 *
	 *		  - if the given buzzer is in the queue, it is
	 *		    moved from its current position to the front
	 *		    of the queue.  1 is returned indicating success
	 *		    of the operation.
	 *		  - if the buzzer is not in the queue, the queue
	 *		    is unchanged and 0 is returned (operation failed).
	 *
	 * Return:  If the buzzer isn't actually currently in the
	 *		queue, the queue is unchanged and false is returned
	 *		(indicating failure).  Otherwise, true is returned.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	bool take_bribe(int buzzer) {


            if(que.size()==0)
               cout << "The person is already 1st!!" << endl;


           return false;  // placeholder



           return true;
        }



};   // end ServiceQueue class

#endif

