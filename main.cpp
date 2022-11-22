#include<bits/stdc++.h>
#include "avl.cpp"
using namespace std;

std::ostream& bold_on(std::ostream& os)
{   
    
    return os << "\e[1m \x1B[31m";
}

std::ostream& bold_off(std::ostream& os)
{
    //system("Color B");
    return os << "\e[0m \033[0m\t\t";
}

vector<pair<string, vector<pair<string, pair<Node*, Node*>>> >> categoriesAlongWithSubcategoriesAndWorkers;

void insertIntoAvailable(int c1, int c2){
    categoriesAlongWithSubcategoriesAndWorkers[c1].second[c2].second.first = insert(categoriesAlongWithSubcategoriesAndWorkers[c1].second[c2].second.first, categoriesAlongWithSubcategoriesAndWorkers[c1].second[c2].second.second->key, categoriesAlongWithSubcategoriesAndWorkers[c1].second[c2].second.second->name, categoriesAlongWithSubcategoriesAndWorkers[c1].second[c2].second.second->phone_number);

}

void removeFromUnavailable(int c1, int c2){
    categoriesAlongWithSubcategoriesAndWorkers[c1].second[c2].second.second = NULL;

}

void insertIntoUnavailable(int c1, int c2){

}



int main(){
    ifstream file_input;
    string line;
    file_input.open("input.txt");

    int numberOfCategories;
    string nameOfCategory;
    int numberOfSubcategories;
    string nameOfSubcategory;
    int numberOfWorkersInACategory;
    string nameOfWorker;
    string phoneNumber;
    Node* searchResult = NULL;
    int index = 0;

    int choice5;

    int z = 0;

    vector<pair<pair<int, int>, int>> arrWithSelectedWorker;


    vector<string> categories;
    
    
    vector<Node*> roots; 
    vector<Node*>::iterator it;
    Node * p = NULL;  
    for(int i = 0; i < 1000; i++){
        roots.push_back(new Node());
    }
    for(it = roots.begin(); it < roots.end(); it++){
        *it = NULL;
    }

    while (file_input) {
        file_input >> line;
        
        numberOfCategories = stoi(line);
        
        
        for(int i = 1; i <= numberOfCategories; i++){
            file_input >> nameOfCategory;
            categories.push_back(nameOfCategory);
            file_input >> line;
            
            numberOfSubcategories = stoi(line);

            vector<pair<string, pair<Node*, Node*>>> temp_subcategoriesAndWorkers;

            for(int j = 0; j < numberOfSubcategories; j++){
                file_input >> nameOfSubcategory;
                file_input >> line;

                numberOfWorkersInACategory = stoi(line);
                vector<pair<Node*, Node*>> temp_workers;

                for(int k = 0; k < numberOfWorkersInACategory; k++){
                    file_input >> nameOfWorker;
                    file_input >> phoneNumber;
                    roots[index] = insert(roots[index], k, nameOfWorker, phoneNumber);

                }
                
                temp_subcategoriesAndWorkers.push_back(make_pair(nameOfSubcategory, make_pair(roots[index], roots[1000-index-1])));
                index++;
            }
            categoriesAlongWithSubcategoriesAndWorkers.push_back(make_pair(nameOfCategory,temp_subcategoriesAndWorkers ));
        }
        break;
    }
    
    file_input.close();

    begin:
    int choice1;
    cout <<endl<<bold_on<< "Categories" <<bold_off<<endl;
    vector<pair<string, vector<pair<string, pair<Node*, Node*>>> >>::iterator it1; int x = 0;
    for(it1 = categoriesAlongWithSubcategoriesAndWorkers.begin(); it1 < categoriesAlongWithSubcategoriesAndWorkers.end(); it1++){
        cout << x++ <<". " <<(*it1).first << endl;
    }
    cout << "Enter your Choice: ";
    cin >> choice1;

    cout <<endl<<bold_on<< "Sub-categories" <<bold_off<<endl;
    vector<pair<string, pair<Node*, Node*>>>::iterator it2; x = 0; int choice2;
    for(it2 = categoriesAlongWithSubcategoriesAndWorkers[choice1].second.begin(); it2 < categoriesAlongWithSubcategoriesAndWorkers[choice1].second.end(); it2++){
        cout << x++ <<". " <<(*it2).first << endl;
    }
    
    cout << "Enter your Choice: ";
    cin >> choice2;

    if(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second!=NULL){
        cout <<bold_on<< "Worker already selected from the category, select another category or free the worker first!" <<bold_off<< endl <<endl;
        goto switchcase;
    }

    cout <<endl<<bold_on<< "Available Workers" <<bold_off<<endl;
    inOrder(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first);
    cout << endl;
    // cout << endl << bold_on << "Non-Available Workers" << bold_off << endl;
    // inOrder(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second);

    int choice3;
    cout << "Select a worker by typing their id: ";
    cin >> choice3;
    
    searchResult = search(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first, choice3);
    if(searchResult!=NULL){
        categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second = insert(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second, searchResult->key, searchResult->name, searchResult->phone_number);
        categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first = deleteNode(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first, choice3);
    }
    
    
    
    arrWithSelectedWorker.push_back(make_pair(make_pair(choice1, choice2), choice3));


    cout <<endl<<bold_on<< "Selected By You:" <<bold_off<<endl;
    inOrderForSelected(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second);
    cout << endl;

    cout << endl;

    switchcase:
    cout << "1. Free a worker" << endl;
    cout << "2. Show selected workers" << endl;
    cout << "3. Select another worker" <<endl;
    cout << "4. Exit" << endl;

    int choice4;
    cin >> choice4;
    cout << endl;

    switch(choice4){
        case 1:
            z = 0;
            for(auto & element : arrWithSelectedWorker){
                cout <<z  << ". " << categoriesAlongWithSubcategoriesAndWorkers[element.first.first].second[element.first.second].second.second->name << endl;
                z++;
            }
            cout << "Enter the key to be deleted" << endl;
            cin >> choice5;
            cout << endl;

            insertIntoAvailable(arrWithSelectedWorker[choice5].first.first, arrWithSelectedWorker[choice5].first.second);
            removeFromUnavailable(arrWithSelectedWorker[choice5].first.first, arrWithSelectedWorker[choice5].first.second);

            arrWithSelectedWorker.erase(find(arrWithSelectedWorker.begin(),arrWithSelectedWorker.end(),arrWithSelectedWorker[choice5]));

            goto switchcase;
        case 2:
            z = 0;
            for(auto & element : arrWithSelectedWorker){
                cout <<z  << ". " << categoriesAlongWithSubcategoriesAndWorkers[element.first.first].second[element.first.second].second.second->name << endl;
                z++;
            }
            cout << endl;
            goto switchcase;
        case 3:
            goto begin;
        case 4:
            break;
        default:
            cout << "Wrong choice\n";
            break;
    }

    return 0;
}