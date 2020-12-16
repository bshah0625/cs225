/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode *curr = head_;
  while(curr != NULL) {
    ListNode *prev;
    prev = curr;
    curr = curr->next;
    delete prev;
  }
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode *curr = new ListNode(ndata);
  if(head_ == NULL) {
    curr->prev = NULL;
    curr->next = NULL;
    head_ = curr;
    tail_ = curr;
  } 
  else {
    curr->prev = NULL;
    curr->next = head_;
    head_->prev = curr;
    head_ = curr;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode *curr = new ListNode(ndata);
  if(tail_ == NULL) {
    curr->prev = NULL;
    curr->next = NULL;
    head_ = curr;
    tail_ = curr;
  } 
  else {
    curr->next = NULL;
    curr->prev = tail_;
    tail_->next = curr;
    tail_ = curr;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {

  if(start==NULL)
  {
    return NULL;
  }

  if(splitPoint<1)
  {
    return start;
  }

  if(length_<splitPoint)
  {
    return NULL;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint-1&& curr != NULL; i++) {
    if(curr->next!=NULL)
      curr = curr->next;
  }

  if (curr != NULL) {
      curr=curr->next;
      curr->prev->next = NULL;
      tail_=curr->prev;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}


/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */

template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* one = head_;
  if(one == NULL){
    return;
  }
  while(one->next != NULL){
    ListNode* two = one->next;
    if(two->next == NULL)
      return;
    ListNode* three = second->next;
    if(three == tail_){
      tail_ = first;
    }
    if(one == head_){
      head_ = second;
    }
    two->prev = one->prev;
    if(two->prev != NULL){
      two->prev->next = two;
    }
    one->next = three->next
    if(one->next != NULL){
      one->next->prev = one;
    }
    three->next = one;
    one->prev = three;
    if(one->next == NULL){
      return;
    }
    one = one->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if(head_ == NULL || tail_ == NULL) 
    return;
  if(startPoint == endPoint) 
    return;

  ListNode *temp = NULL;
  ListNode *curr = startPoint;
  ListNode *original_start = startPoint;
  ListNode *original_start_prev = startPoint->prev;
  ListNode *original_end = endPoint;
  ListNode *original_end_next = endPoint->next;

  while(curr != endPoint) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }

  temp = curr->prev;
  curr->prev = original_start_prev;
  curr->next = temp;
  endPoint = original_start;
  endPoint->next = original_end_next;

  if(original_start_prev == NULL){
    head_ = curr;
  } else {
    original_start_prev->next = original_end;
  }
  if(original_end_next == NULL) {
    tail_ = endPoint;
  } else {
    original_end_next->prev = original_start;
  }

}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if(length_ == 0 || length_ == 1) return;
  ListNode *startPoint = head_;
  ListNode *endPoint = head_;

  while(endPoint != NULL){
    for(int i = 0; i < n - 1; i++) {
      if(endPoint->next == NULL){
        reverse(startPoint, endPoint);
        return;
      }
      endPoint = endPoint->next;
    }
    reverse(startPoint, endPoint);
    if(endPoint->next == NULL) return;
    else {
      startPoint = endPoint->next;
      endPoint = startPoint;
    }
  }
}



/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  ListNode *temp = NULL;
  ListNode *firstv = first;
  ListNode *tempf = first;
  ListNode *temps = second;
  if(first->data < second->data)
  {
        firstv = tempf;
        tempf = tempf->next;
  }
  else
  {
        firstv = temps;
        temps = temps->next;
  }

  temp = firstv;

  while(temps != NULL && tempf != NULL)
  {

      if(tempf == NULL && temps== NULL)
      {
        break;
      }

      else if(tempf == NULL ||
              (temps->data < tempf->data && temps != NULL) )
      {
        temp->next = temps;
        temp->next->prev = temp;
        temps = temps->next;
        temp = temp->next;
      }
      else
      {
        temp->next = tempf;
        temp->next->prev = temp;
        tempf = tempf->next;
        temp = temp->next;
      }
  }
  if(temps == NULL)
  {
    temp->next = tempf;
    tempf->prev = temp;
  }
  if(tempf == NULL)
  {
    temp->next = temps;
    temps->prev = temp;
  }
 


  return firstv;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if (chainLength == 1){
	  return start;
  }
  else {
	  int currLength = chainLength/2;
	  ListNode *temp;
	  temp = split(start, currLength);
	  ListNode *begin = mergesort(start, currLength);
	  ListNode *end = mergesort(temp, chainLength - currLength);
	  return merge(begin, end);
  }
}

