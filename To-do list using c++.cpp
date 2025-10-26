#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
typedef struct task
{
    string task;
    int status = 0;
    struct task *next;
} task;
task *list_creation(task *head)
{
    head=new task;
    cout << endl
         << "Enter task 1 : ";
    getline(cin, head->task);
    cout<<head->task;
    task *current,*temp;
    current = head;
    int choice;
    while (choice)
    {
        cout << endl
             << "Enter 1 to add a task and 0 to end the list : ";
        cin >> choice;
        if (choice == 1)
        {
            temp =new task;;
            cout << "Enter the task : ";
            getline(cin, temp->task);
            current->next = temp;
            current = temp;
        }
    };
    current->next = nullptr;
    return head;
}
void display_list(task *head)
{
    task *temp;
    int i = 1;
    do
    {
        cout << endl
             << "Task " << i << ": ";
        cout << temp->task;
        cout << "(Status : )";
        if (temp->status == 0)
        {
            cout << "Incomplete";
        }
        else
        {
            cout << "Completed";
        }
        i++;
        temp = temp->next;
    } while (temp->next != nullptr);
    return;
}
task *remove_task(task *head)
{
	task *temp, *prev;
    int pos;
    cout<<endl<<"Enter the task no. to be deleted : ";
    cin>>pos;
	temp =new task;
	if (pos == 1)
	{
		temp = head;
		head = temp->next;
		return head;
	}
	else
	{
		int count = 1;
		prev = head;
		while (count < (pos - 1))
		{
			prev = prev->next;
			count++;
		}
		temp = prev->next;
		prev->next = temp->next;
		return head;
	}

}
task *update_status(task *head)
{
    task *prev;
    int pos;
    cout<<endl<<"Enter the task no. to be updated : ";
    cin>>pos;
	if (pos == 1)
	{
		head->status=1;
		return head;
	}
	else
	{
		int count = 1;
		prev = head;
		while (count < (pos - 1))
		{
			prev = prev->next;
			count++;
		}
        prev->next->status=1;
		return head;
	}
}
int main()
{
    int choice;
    task *head = nullptr;
    while(choice)
    {
        cout << endl
             << "Enter 1 for creating a new list\n"
             << "Enter 2 to display the list\n"
             << "Enter 3 to delete a task from the list\n"
             << "Enter 4 to mark a task as completed\n"
             << "Enter 0 to end the code" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            head = list_creation(head);
            break;
        case 2:
            display_list(head);
            break;
        case 3:
            head = remove_task(head);
            break;
        case 4:
            head = update_status(head);
            break;
        }
    };
    cout<<"\nThank you";
}
