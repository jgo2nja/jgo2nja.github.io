// Creator: James O'Connell jgo2nja
import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class StringSorter {
	// Declare fields
	private Queue<String>[] arrOfQ;
	private ArrayList<String> returnList = new ArrayList<String>();
	
	public StringSorter() {
		// Initialize the queues
		this.arrOfQ = new Queue[26];
		for (int i = 0; i < 26; i++) {
			this.arrOfQ[i] = new LinkedList<String>();
		}
	}
	
	public ArrayList<String> sort(ArrayList<String> arr) {
		// First, distribute the initial strings into queues. Next, call collect
		this.distribute(arr, 0);
		return this.collect(0);
	}
	
	public void distribute(ArrayList<String> arr, int i) {
		// Iterate through all elements in the input list
		for (int j = 0; j < arr.size(); j++) {
			String compareString = arr.get(j);
			// Prevent an index out of bounds exception
			if (i >= compareString.length()) {
				this.returnList.add(compareString);
			} 
			// Use compareTo to generate an integer representation of the queue
			else {
			String reduceString = compareString.substring(i,i+1);
			int queuePosition = reduceString.compareTo("a");
			this.arrOfQ[queuePosition].add(compareString);
			}
		}
	}
	
	public ArrayList<String> collect(int i) {
		// Iterate through all queues
		for (int n = 0; n < 26; n++) {
			// If the queue only contains one element, add it to the list
			if (this.arrOfQ[n].size() == 1) {
				this.returnList.add(this.arrOfQ[n].peek());
				}
			if (this.arrOfQ[n].size() > 1) {
			// Otherwise, recursively iterate the queues until fully sorted
				ArrayList<String> temp = new ArrayList<String>();
				temp.addAll(this.arrOfQ[n]);
				StringSorter s1 = new StringSorter();
				s1.distribute(temp, i+1);
				this.returnList.addAll(s1.collect(i+1));
			}
		}
		// Reset the global variable for multiple uses
		ArrayList<String> reset = new ArrayList<String>();
		reset.addAll(this.returnList);
		this.returnList = new ArrayList<String>();
		return reset;
		}
	public static void main(String[] args) {
		// test collect and distribute
		ArrayList<String> testList = new ArrayList<String>();
		testList.add("ja");
		testList.add("o");
		testList.add("j");
		StringSorter testSorter = new StringSorter();
		testSorter.distribute(testList, 0);
		System.out.println(testSorter.arrOfQ[9]);
		System.out.println(testSorter.collect(0));
		// test sort
		ArrayList<String> testList1 = new ArrayList<String>();
		testList1.add("james");
		testList1.add("john");
		testList1.add("olivia");
		testList1.add("jamie");
		testList1.add("andrew");
		StringSorter testSorter1 = new StringSorter();
		System.out.println(testSorter1.sort(testList1));
	}
}
