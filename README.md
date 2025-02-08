# Garage-Locator

Terminal Based:

The task is to implement an efficient Garage Locator System for a campus represented as a Cartesian plane. Users can locate garages near their position and query specific coordinates to check for a garage and its rank in a sorted list.

The program's key features include:

Sorting Garages by Distance: Garages are sorted by their Euclidean distance from the user's location. If two garages are equidistant, they are sorted by x-coordinate (ascending), and further ties are broken by y-coordinate (ascending).

Custom Sorting Algorithm: A combination of Merge Sort and Insertion Sort is used, controlled by a threshold t. Subsections with size <= t are sorted using Insertion Sort, while larger sections are sorted using recursive Merge Sort.

Binary Search for Queries: A Binary Search function efficiently checks if a queried point contains a garage and determines its position in the sorted list.
