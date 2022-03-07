#pragma once
#include "Oferta.h"
#include <assert.h>
#include "Repository.h"
#include "Controller.h"
#include "utils.h"
#include "exceptii.h"
#include <exception>

/*
* test pentru domain
* assertion error daca pica testele
*/
void test_domain();

/*
* test pentru repository
* assertion error daca pica testele
*/
void test_repository();

/*
* test pentru controller , mai exact partea de adaugare, stergere, cautare, modificare
* assertion error daca pica testele
*/
void test_controller_ascm();

/*
* test pentru controller , mai exact partea de filtrare
* assertion error daca pica testele
*/
void test_controller_filtru();

/*
* test pentru controller , mai exact partea de sortare
* assertion error daca pica testele
*/
void test_controller_sort();

/*
* test pentru controller , mai exact partea de validare
* assertion error daca pica testele
*/
void test_validare();

/*
* test pentru obiectul VectorDinamic
* assertion error daca pica testele
*/
void test_VectorDinamic();

/*
* ruleaza toate testele de mai sus
* assertion error daca pica testele
*/
void toate_testele();

/*
* test pentru obiectul Wishlist si alte functionalitati necesare obiectului
* assertion error daca pica testele
*/
void test_wishlist();

/*
* test functionalitate dictionar din Controller
* assertion error daca pica testele
*/
void test_dictionar_controller();

//void test_repo_file();

void test_undo();

void test_exception_repo();