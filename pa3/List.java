// Billy Kwong
// bqkwong
// Pa3
// List.java

public class List {
	
	private class Node {
		// Fields
		Object data;
		Node next;
		Node prev;

		// Constructor
		Node(Object data) {
			this.data = data;
			next = null;
			prev = null;
		}

		// toString: Overides Object's toString method.
		public String toString() {
			return String.valueOf(data);
		}
	}

	// Fields
	private Node front;
	private Node back;
	private Node cursor;
	private int length;

	// Constructor
	// Creates new list.
	List() {
		front = back = cursor = null;
		length = 0;
	}

	// Access functions
	
	// Returns the number of elements in this List.
	int length() {
		return length;
	}

	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index() {
		if (cursor == null)
			return -1;
		Node N = front;
		int index = 0;
		while (N != null) {
			if (N.data == cursor.data)
				return index;
			index++;
			N = N.next;
		}
		return -1;
	} 

	// Returns front element. Pre: length()>0
	Object front() {
		if (length() > 0)
			return front.data;
		return -1;
	}

	// Returns back element. Pre: length()>0
	Object back() {
		if (length() > 0)
			return back.data;
		return -1;
	}

	// Returns cursor element. Pre: length()>0, index()>=0
	Object get() {
		if (length() > 0 && index() >= 0)
			return cursor.data;
		return -1;
	}

	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	public boolean equals(Object x) {
		boolean flag = true;
		if (x instanceof List) {
			List L = (List) x;
			Node A = this.front;
			Node B = L.front;
			if (this.length == L.length) {
				while (flag && A != null) {
					flag = (A.data.equals(B.data));
					A = A.next;
					B = B.next;
				}
				return flag;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	
	// Manipulation procedures
	
	// Resets this List to its original empty state.
	void clear() {
		front = null;
		back = null;
		length = 0;
		cursor = null;
	}

	// If List is non-empty, places the cursor under the front
	// element, otherwise does nothing.
	void moveFront() {
		if (length() > 0) {
			cursor = front;
		}
	}

	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack() {
		if (length() > 0) {
			cursor = back;
		}
	}

	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev() {
		if (index() == -1) {
			return;
		}
		if (index() == 0) {
			cursor = null;
		}
		if (index() >= 0 && index() <= length() - 1) {
			cursor = cursor.prev;
		} 
	}

	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext() {
		if (index() == -1) {
			return;
		}
		if (index() == length() - 1) {
			cursor = null;
		}
		if (index() >= 0 && index() <= length() - 1) {
			cursor = cursor.next;
		}
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(Object data) {
		List.Node N = new List.Node(data);
		if (length() > 0) {
			N.next = front;
			front.prev = N;
			front = front.prev;
		}
		if (length() == 0) {
			front = N;
			back = N;
		}
		length++;
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(Object data) {
		List.Node N = new List.Node(data);
		if (length() > 0) {
			back.next = N;
			N.prev = back;
			back = back.next;
		}
		if (length() == 0) {
			front = N;
			back = N;
		}
		length++;
	}

	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(Object data) {
		if (length() > 0 && index() >= 0) {
			if (index() == 0) {
				prepend(data);
				return;
			}
			List.Node N = new List.Node(data);
			N.next = cursor;
			N.prev = cursor.prev;
			cursor.prev.next = N;
			cursor.prev = N;
		}
		length++;
	}

	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(Object data) {
		if (length() > 0 && index() >= 0) {
			if (index() == length() - 1) {
				append(data);
				return;
			}
			List.Node N = new List.Node(data);
			N.next = cursor.next;
			N.prev = cursor;
			cursor.next.prev = N;
			cursor.next = N;
		}
		length++;
	}

	// Deletes the front element. Pre: length()>0
	void deleteFront() {
		if (length() < 0) {
			return;
		}
		if (index() == 0)
			cursor = null;
		if (length() == 1) {
			clear();
			return;
		}
		front = front.next;
		front.prev = null;
		length--;
	}

	// Deletes the back element. Pre: length()>0
	void deleteBack() {
		if (length() < 0)
			return;
		if (index() == length() - 1)
			cursor = null;
		if (length() == 1) {
			clear();
			return;
		}
		back = back.prev;
		back.next = null;
		length--;
	}

	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	// Other methods
	void delete() {
		List.Node N = cursor;
		if (length() == 0) {
			return;
		}
		if (front == cursor) {
			deleteFront();
			return;
		}
		if (back == cursor) {
			deleteBack();
			return;
		}
		if (length() > 0 && index() >= 0) {
			if (N != null) {
				cursor.prev.next = cursor.next;
				cursor.next.prev = cursor.prev;
				cursor = null;
			}
		}
		length--;
	}

	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString() {
		String str = "";
		List.Node N = front;
		while (N != null) {
			if (N == back) {
				str += N.data;
				N = N.next;
				break;
			}
			str += N.data + " ";
			N = N.next;
		}
		return str;
	}

	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	public List copy() {
		List C = new List();
		List.Node traverse = front;
		while (traverse != null) {
			C.append(traverse.data);
			traverse = traverse.next;
		}
		return C;
	}
}