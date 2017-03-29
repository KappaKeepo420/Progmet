/* Behorende bij Programmeertechnieken huiswerk 3: unit testing.
 *
 * Let op: het is mogelijk dat de code nog aan aantal bugs bevat,
 * probeer deze te vinden door unit tests te schrijven.
 */

#include <cstdint>
#include <stdexcept>


template <typename T>
class MyStack
{
  private:
    struct Link
    {
      Link *next;
      T item;

      Link(T item)
        : next(nullptr), item(item)
      { }
    };

    Link *head;
    Link *tail;

    Link *find_link_before(const Link *target) const noexcept
    {
      Link *link(head);
      for ( ; link != nullptr; link = link->next)
        if (link->next == target)
          return link;

      return nullptr;
    }

  public:
    MyStack() noexcept
      : head(nullptr), tail(nullptr)
    { }

    ~MyStack() noexcept
    {
      if (head)
        delete head;
      if (tail)
        delete tail;
    }

    /* Pushes item on the stack. */
    void push(T item)
    {
      if (is_empty())
        head = tail = new Link(item);
      else
        {
          tail->next = new Link(item);
          tail = tail->next;
        }
    }

    /* Pushes a series of items on the stack, use for example as follows:
     *
     *   MyStack<int> stack;
     *   std::vector<int> vector{50, 60, 70, 80};
     *   stack.push_multiple(vector.begin(), vector.end());
     *
     * Note: The MyStack and vector must be containers for the same
     * type.
     */
    template <typename InputIterator>
    void push_multiple(InputIterator first, InputIterator last)
    {
      static_assert(std::is_same<T, typename InputIterator::value_type>::value,
              "Types must be the same.");

      for (InputIterator it = first; it != last; ++it)
        push(*it);
    }

    /* Pushes a series of items on the stack given using an initializer
     * list. Use for example as follows:
     *
     *   MyStack<int> stack;
     *   stack.push_multiple({10, 20, 30, 40});
     */
    void push_multiple(std::initializer_list<T> il)
    {
      for (const auto &value : il)
        push(value);
    }

    /* Returns value on top of stack. Throws exception when stack is
     * empty.
     */
    T peek(void) const
    {
      if (is_empty())
        throw std::out_of_range("Stack is empty");

      return tail->item;
    }

    /* Pops value on top of stack. Throws exception when stack is empty.
     */
    T pop(void)
    {
      if (is_empty())
        throw std::out_of_range("Stack is empty");

      Link *link(tail);
      Link *before_tail(find_link_before(tail));

      /* Set tail to the link before tail */
      if (before_tail == nullptr)
        head = tail = nullptr;
      else
        tail = before_tail;

      T ret = link->item;
      delete link;

      return ret;
    }

    /* Removes all items from the stack. Upon completion of the function
     * the stack will be empty.
     */
    void clear(void) noexcept
    {
      if (is_empty())
        return;

      Link *link(head);
      while (link != nullptr)
        {
          Link *current(link);
          link = link->next;
          delete current;
        }

      head = tail = nullptr;
    }

    /* Returns whether the stack is empty. */
    bool is_empty(void) const noexcept
    {
      return tail == nullptr;
    }

    /* Returns the number of elements stored on the stack. */
    std::size_t size(void) const noexcept
    {
      if (is_empty())
        return 0;

      size_t len(0);
      for (Link *link = head; link != nullptr; link = link->next)
        ++len;

      return len;
    }
};
