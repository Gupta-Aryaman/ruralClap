if(searchResult!=NULL){
        categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second = insert(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second, searchResult->key, searchResult->name, searchResult->phone_number);
        categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first = deleteNode(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first, choice3);
    }