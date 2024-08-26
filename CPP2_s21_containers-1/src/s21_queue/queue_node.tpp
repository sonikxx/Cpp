#ifndef QUEUE_NODE_TPP
#define QUEUE_NODE_TPP

template <typename T>
struct Node {
 public:
  T data;
  Node *next;
  Node(T data) : data(data), next(nullptr) {}
};

#endif