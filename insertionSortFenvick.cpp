#include <iostream>
#include <algorithm>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

struct node
{
    int value;
    int original_position;
    int query_index;
    bool is_query;
    int query_priority;

    bool operator<(node const &other)
    {
        if (value == other.value)
        {
            return query_priority < other.query_priority;
        }
        return value < other.value;
    }
};

void update(int *Bit, int n, int index)
{
    while (index <= n)
    {
        Bit[index] += 1;
        index += index & (-index);
    }
}

int query(int *Bit, int index)
{
    int ans = 0;
    while (index > 0)
    {
        ans += Bit[index];
        index -= index & (-index);
    }
    return ans;
}

bool comp(node a, node b)
{
    if (a.value == b.value)
    {
        if (a.query_priority == b.query_priority)
        {
            return a.query_index > b.query_index;
        }
        return a.query_priority > b.query_priority;
    }
    return a.value > b.value;
}

int insertionSort(vector<int> old_arr)
{
    long long shifts = 0;
    // int n = sizeof(old_arr) / sizeof(old_arr[0]);
    int n = old_arr.size();
    int arr[n + n - 1];

    for (int i = 0; i < n; i++)
    {
        arr[i] = old_arr[i];
    }
    for (int i = n; i < n + n - 1; i++)
    {
        arr[i] = old_arr[i - (n - 1)];
    }

    // declare empty array for nodes
    node node_arr[2 * n];

    //  create array of nodes
    // fill array of nodes
    for (int i = 1; i < n + 1; i++)
    {
        node_arr[i].value = arr[i - 1];
        node_arr[i].original_position = i;
        node_arr[i].is_query = false;
        node_arr[i].query_priority = 0;
    }

    for (int i = n + 1; i < 2 * n; i++)
    {
        node_arr[i].value = arr[i - 1];
        node_arr[i].query_index = i - n + 1;
        node_arr[i].is_query = true;
        node_arr[i].query_priority = 100;
    }

    // sort array of nodes
    sort(node_arr + 1, node_arr + 2 * n, comp);

    int Bit[n + 1];
    memset(Bit, 0, sizeof(Bit));

    for (int i = 1; i < 2 * n; i++)
    {
        if (node_arr[i].is_query)
        {
            shifts += query(Bit, node_arr[i].query_index);
        }
        else
        {
            update(Bit, n + 1, node_arr[i].original_position);
        }
    }

    return shifts;
}

main()
{
    vector<int> arr1{2, 1, 3, 1, 2};
    // vector<int> arr1{5, 4, 3, 2, 1};
    vector<int> arr2;
    for (int i = 1; i <= 50000; i++)
    {
        arr2.push_back(i);
    }
     
    cout << "Counting:\n";
    int shifts = insertionSort(arr2);

    cout << "No of shifts: " << shifts << endl;

    return 0;
}