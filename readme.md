# Inventory management  

## purpose 
Medicine Inventory management and transportation of items It is an inventory-handle program that provides a way to store and manage newly added items by section.
There is a **possibility** of developing a user interface in the future  

## Project Period
Nov 3rd ~ Nov 26th 2023 : Individually Ended


## Currently Updated Features
-> interface for adding and changing inventory: nov 29th  
-> Change to a more direct interface (Easily understandable): nov 29th  
-> Added validation formulas for memory usage ,optimization and residual data decomposition: Dec 2nd  
-> Errors by duplecate Item fetched: Dec 2nd  
=> your welcome for contact me for colaborate using this basic forms.  
- Email: a24738598@gmail.com  , Phone: 647-879-3598


## Operable Files

**Aidman**  
A core assistant file that connects product registration and various functions such as search, storage, and delivery for medicine.  
[AidMan](Programfiles/AidMan.cpp), [Header](Programfiles/AidMan.h), [Testers](testingfiles/Aidman_test.cpp)

**Date**  
A file that handles the date class that makes adjustments through various validations.  
[Date](Programfiles/Date.cpp), [Header](Programfiles/Date.h), [Testers](testingfiles/Date_test.cpp)

**iProduct**  
Features responsible for input/output interfaces.  
[iProduct](Programfiles/iProduct.cpp), [Header](Programfiles/iProduct.h), [Testers](testingfiles/iProduct_test.cpp)

**Item**  
Store additional data with iProduct's inheritance class Provides status management operations for products.  
[Item](Programfiles/Item.cpp), [Header](Programfiles/Item.h), [Testers](testingfiles/Item_test.cpp)

**Perishable**  
It is a section that manages certain products inherited from Item Class, and is responsible for classifying shelf life and perishable products.  
[Perishable](Programfiles/Perishable.cpp), [Header](Programfiles/Perishable.h), [Testers](testingfiles/Perishable_test.cpp)

**Status**  
It is functional to handle all **item** inventory and health management helper functions.  
[Status](Programfiles/Status.cpp), [Header](Programfiles/Status.h), [Testers](testingfiles/Status_test.cpp)

**Utils**  
Additional function for effeciency.  
[Utils](Programfiles/Utils.cpp), [Header](Programfiles/Utils.h)

## Compile In remote 
G++ compiler required  

```bash
g++ -Wall -std=c++17 -g -o main main.cpp AidMan.cpp Item.cpp Perishable.cpp Status.cpp Utils.cpp
```
Using SSH will be good

## How to test local
[TestingCodes](testingfiles/)
Sequence to test my codes.

### 1. Clone repo

Clone my repo to your local

```bash
git clone https://github.com/daeuk23/Medicine-Inventory-management.git
cd AidManProject
```  

### 2. move textfile

File Integration for testing

```bash
mkdir -p programfiles
mv testingfiles/*.cpp programfiles/
```

### 3. compile

compile the tester files

```bash
cd Programfiles
g++ test_filename.cpp -o test_run
./test_run
```
=> modify test_filename to actual tester name


**All the files except main.cpp,test helpers(which Created by [fardad soleimanloo](https://github.com/fardad)) Are Created by Daeuk Kim**
