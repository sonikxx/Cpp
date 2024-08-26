#ifndef LIST_NODE_TPP
#define LIST_NODE_TPP

template <typename T>
struct ListNode {
  T data;
  ListNode *next;
  ListNode *prev;
  ListNode(T data) : data(data), next(nullptr), prev(nullptr) {}
};

#endif  // LIST_NODE_TPP