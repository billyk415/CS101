// Billy Kwong
// bqkwong
// List.java

public class List{
	
	private class Node{
		// Fields
		int data;
		Node next;
		Node prev;
		
		// Constructors
		Node(int data){
			this.data = data;
			next = null;
			prev = null;
		}
		// toString()
		// Overrides Object's toString() method.
		public String toString() {
			return String.valueOf(data);
		}
	}
	
	// Fields
	private Node front;
	private Node back;
	private Node cursor;
	private int index;
	private int length;
	
	

	// Constructor
	//Creates a new empty list.
	List(){
		front = back = cursor = null;
		index = -1;
		length = 0;
	}

	// Access functions
	
	// Returns the number of elements in this List.
	int length(){
		return length;
	}
	
	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index(){
		if (length() <= 0)
			return -1;
		return index;
	}
	
	// Returns front element. Pre: length()>0
	int front(){
		if (length <= 0)
			throw new RuntimeException("List error: front() called on empty list.");
		return front.data;
	}
		
	// Returns back element. Pre: length()>0
	int back(){
		if (length <= 0)
			throw new RuntimeException("List error: back() called on empty list.");
		return back.data;
	}
	
	// Returns cursor element. Pre: length()>0, index()>=0
	int get(){
		if (length <= 0)
			throw new RuntimeException("List Error: get() called on empty list.");
		if (index < 0)
			throw new RuntimeException("List Error: get() called on invalid index.");   
		return cursor.data;
	}
	
	// Returns true if and only if this List and L are the same
	// integer sequence. The states of the cursors in the two Lists
	// are not used in determining equality.
	boolean equals(List L){
		boolean equals  = true;
		Node N = this.front;
		Node M = L.front;
		if (this.length == L.length){
			while (equals && N != null){
			equals = (N.data == M.data);
			N = N.next;
			M = M.next;
		}
		return equals;
		}
		else return false;
	}	
	 
	// Manipulation procedures
	
	// Resets this List to its original empty state.
	void clear(){
		front = back = cursor = null;
		index = -1;
		length = 0;
	}
	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront(){ 
		if (length > 0){ 
			cursor = front;
			index = 0;
		}
	}
	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack(){
		if (length > 0){
			cursor = back;
			index = length - 1;
		}
	}
	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev(){
		if (cursor != null && index != 0){
			cursor = cursor.prev;
			index--;
		}
		else if (cursor != null && index == 0){
			cursor = null;
			index = -1;
		}
	}
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext() {
		if (cursor != null && index != length-1){
			cursor = cursor.next;
			index++;
		}
		else if (cursor != null && index == length-1){
			cursor = null;
			index = -1;
		}
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(int data){
		Node N;
		if (front == null){
			front = new Node(data);
			back = front;
			cursor = front;
		}
		else{
			N = front;
			N.prev = new Node(data);
			front = N.prev;
			front.next = N;
		} 
		length++;
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(int data){
		Node N;
		if (back == null){
			back = new Node(data);
			front = back;
			cursor = back;
		} 
		else{
			N = back;
			N.next = new Node(data);
			back = N.next;
			back.prev = N;
		}
		length++;
	}
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(int data){
		if (length <= 0 || index < 0)
			throw new RuntimeException( "List Error: insertBefore() called on an empty list.");
		else{
			if (index == 0)
				prepend(data);
		else{
			Node N = new Node(data);
			Node before = cursor.prev;
			N.prev = before;
			N.next = cursor;
			before.next = N;
			cursor.prev = N;
			length++;
			index++;
			}
		}
	}
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(int data){
		if (length <= 0 || index < 0)
			throw new RuntimeException("List Error: insertAfter() called on empty list");
		else{
			if (index == length -1)
				append(data);
		else {
			Node N = new Node(data);
			Node after = cursor.next;
			N.next = cursor.next;
			N.prev = after;
			after.prev = N;
			cursor.next = N;
			length++;
			}
		}
	}
	// Deletes the front element. Pre: length()>0
	void deleteFront(){
		if (length <= 0) throw new RuntimeException("List Error: deleteFront() called on empty list");
		if (cursor == front){
			cursor = null;
			index = -1;
		}
		front = front.next;
		front.prev = null;
		length--;
	}
	// Deletes the back element. Pre: length()>0
	void deleteBack(){
		if (length <= 0) throw new RuntimeException("List Error: deleteBack() called on empty list");
		if (cursor == back){
			cursor = null;
			index = -1;
		}
		back = back.prev;
		back.next = null;
		length--;
	}
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete(){
		if (length() <= 0 || index() < 0) throw new RuntimeException("List Error: delete() called on an empty list.");
		else{
		cursor.prev.next = cursor.next;
		cursor.next = cursor.prev;
		cursor = null;
		index = -1;
		length--;
		}
	}
	 
	// Other methods
	
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString(){
		String str = " ";
		Node N = front;
		while (N != null){
			str += N.toString() + " ";
			N = N.next;
		}
		return str;
	}
	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	List copy() {
		List Q = new List();
		Node N = this.front;
		while (N != null) {
			Q.append(N.data);
			N = N.next;
		}
		return Q;
	}
}
