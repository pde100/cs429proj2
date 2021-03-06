/**************************************************************************
 * C S 429 EEL interpreter
 * 
 * eval.c - This file contains the skeleton of functions to be implemented by
 * you. When completed, it will contain the code used to evaluate an expression
 * based on its AST.
 * 
 * Copyright (c) 2021. S. Chatterjee, X. Shen, T. Byrd. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include "ci.h"

#include "string.h"

/* Function interfaces */

/* Returns true if the given token is a binary operator and false otherwise */
extern bool is_binop(token_t);
/* Returns true if the given token is a unary operator and false otherwise */
extern bool is_unop(token_t);
/* It might be helpful to note that TOK_QUESTION is the only ternary operator. */

char *strrev(char *str);


/* infer_type() - set the type of a non-root node based on the types of children
 * Parameter: A node pointer, possibly NULL.
 * Return value: None.
 * Side effect: The type field of the node is updated.
 * (STUDENT TODO)
 */

static void infer_type(node_t *nptr) {
    // check running status - you can ignore this
    if (terminate || ignore_input) return;
    // Week 1 TODO: Implement a recursive post-order traversal of the AST. Remember to include a base case.
    //print_tree(nptr);
    if(nptr == NULL) {
        return;
    }
    switch (nptr->node_type) {
        // For each week, you will also need to include error checking for each type.
        // Week 1 TODO: Implement type inference for all operators on int and bool types.
        // Week 2 TODO: Extend type inference to handle operators on string types.
        // Week 3 TODO: Implement type evaluation for variables.
        case NT_INTERNAL:
            switch (nptr->tok) {
                // For reference, the identity (do nothing) operator is implemented for you.
                case TOK_IDENTITY:
                    infer_type(nptr->children[0]);
                    nptr->type = nptr->children[0]->type; 
                    
                    break;
                //TODO: unary operator tokens
                case TOK_UMINUS:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[1] != NULL || nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == INT_TYPE) {
                        nptr->type = INT_TYPE;
                        break;
                    } else if(nptr->children[0]->type == STRING_TYPE) {
                        nptr->type = STRING_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    }
                case TOK_NOT:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[1] != NULL || nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == BOOL_TYPE) {
                        nptr->type = BOOL_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    }
                //binary operator tokens
                case TOK_PLUS: // if node is a plus
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE) {
                        nptr->type = INT_TYPE;
                        break;
                    } else if(nptr->children[0]->type == STRING_TYPE && nptr->children[1]->type == STRING_TYPE) {
                        nptr->type = STRING_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    }   
                case TOK_BMINUS:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE) {
                        nptr->type = INT_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    } 
                case TOK_TIMES:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE) {
                        nptr->type = INT_TYPE;
                        break;
                    } else if (nptr->children[0]->type == STRING_TYPE && nptr->children[1]->type == INT_TYPE) {
                        nptr->type = STRING_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    } 
                case TOK_DIV:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE) {
                        nptr->type = INT_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    }
                case TOK_MOD:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE) {
                        nptr->type = INT_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    }  
                case TOK_AND:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == BOOL_TYPE && nptr->children[1]->type == BOOL_TYPE) {
                        nptr->type = BOOL_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    }
                case TOK_OR:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == BOOL_TYPE && nptr->children[1]->type == BOOL_TYPE) {
                        nptr->type = BOOL_TYPE;
                        break;
                    } else {
                        handle_error(ERR_TYPE);
                        break;
                    }
                case TOK_LT:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == BOOL_TYPE || nptr->children[1]->type == BOOL_TYPE) {
                        handle_error(ERR_TYPE);
                        break;
                    } else {
                        nptr->type = BOOL_TYPE;
                        break;
                    } 
                case TOK_GT:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == BOOL_TYPE || nptr->children[1]->type == BOOL_TYPE) {
                        handle_error(ERR_TYPE);
                        break;
                    } else {
                        nptr->type = BOOL_TYPE;
                        break;
                    } 
                case TOK_EQ:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type == BOOL_TYPE || nptr->children[1]->type == BOOL_TYPE) {
                        handle_error(ERR_TYPE);
                        break;
                    } else {
                        nptr->type = BOOL_TYPE;
                        break;
                    }
                case TOK_ASSIGN:
                    for (int i = 0; i < 3; ++i) {
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[2] != NULL) {
                        handle_error(ERR_TYPE);
                        break;
                    }
                    if(nptr->children[0]->type != ID_TYPE || nptr->children[1]->type == ID_TYPE) {
                        handle_error(ERR_TYPE);
                        break;
                    } else {
                        nptr->type = nptr->children[1]->type;
                        break;
                    }
                    break;
                //TODO: ternary operator types
                case TOK_QUESTION:
                    for (int i = 0; i < 3; ++i) {
                        if(nptr->children[i] == NULL) {
                        handle_error(ERR_TYPE);
                            break;
                        }
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[0]->type != BOOL_TYPE) {
                        handle_error(ERR_TYPE);
                        break;
                    } else {
                        if(nptr->children[1]->type == nptr->children[2]->type) {
                            nptr->type = nptr->children[2]->type;
                            break;
                        } else {
                        handle_error(ERR_TYPE);
                            break;
                        }
                    }
                case TOK_COLON:
                    for (int i = 0; i < 3; ++i) {
                        if(nptr->children[i] == NULL) {
                        handle_error(ERR_TYPE);
                            break;
                        }
                        infer_type(nptr->children[i]);
                    }
                    if(nptr->children[0]->type != BOOL_TYPE) {
                        handle_error(ERR_TYPE);
                        break;
                    } else {
                        if(nptr->children[1]->type == nptr->children[2]->type) {
                            nptr->type = nptr->children[2]->type;
                            break;
                        } else {
                        handle_error(ERR_TYPE);
                            break;
                        }
                    }
                default:
                    break;
            }
        case NT_LEAF:
            switch (nptr->tok) {
                case TOK_ID:;
                    //nptr->type = ID_TYPE;
                    //or we could look into hash table to pull correct value
                    entry_t* curr = get(nptr->val.sval);
                    if(curr == NULL) {
                        handle_error(ERR_UNDEFINED);
                        return;
                    }
                    nptr->type = curr->type;
                    break;   
                default:
                    break;
            }
        default:
            break;
    }
    return;
}

/* infer_root() - set the type of the root node based on the types of children
 * Parameter: A pointer to a root node, possibly NULL.
 * Return value: None.
 * Side effect: The type field of the node is updated. 
 */

static void infer_root(node_t *nptr) {
    if (nptr == NULL) return;
    // check running status
    if (terminate || ignore_input) return;

    // check for assignment
    if (nptr->type == ID_TYPE) {
        infer_type(nptr->children[1]);

    } else {
        for (int i = 0; i < 3; ++i) {
            infer_type(nptr->children[i]);
        }
        if (nptr->children[0] == NULL) {
            logging(LOG_ERROR, "failed to find child node");
            return;
        }
        nptr->type = nptr->children[0]->type;
    }
    return;
}

/* eval_node() - set the value of a non-root node based on the values of children
 * Parameter: A node pointer, possibly NULL.
 * Return value: None.
 * Side effect: The val field of the node is updated.
 * (STUDENT TODO) 
 */

static void eval_node(node_t *nptr) {
    //printf("weve reached eval node \n");
    // check running status - you can ignore this.
    if (terminate || ignore_input) return;

    // Week 1 TODO: Implement a recursive post-order traversal of the AST. Remember to include a base case.
    if(nptr == NULL) {
        return;
    }
    switch (nptr->node_type) {
        case NT_INTERNAL:
            // Week 1 TODO: Implement evaluation for all operators on int and bool types.
            // Week 2 TODO: Extend evaluation to handle operators on string types.
        
            if (is_unop(nptr->tok)) {
                for (int i = 0; i < 3; ++i) {
                    eval_node(nptr->children[i]);
                }
                //unary operators
                switch (nptr->tok) {
                    case TOK_UMINUS:
                        if(nptr->type == INT_TYPE) {
                            nptr->val.ival = nptr->children[0]->val.ival * -1;
                        } else {
                            nptr->val.sval = strrev(nptr->children[0]->val.sval);
                        }
                        break;
                    case TOK_NOT:
                        nptr->val.bval = !nptr->children[0]->val.bval;
                        break;
                    default:
                        break;
                }
            }
            if (is_binop(nptr->tok)) {
                for (int i = 0; i < 3; ++i) {
                    eval_node(nptr->children[i]);
                }
                //binary operators
                switch (nptr->tok) {
                    case TOK_PLUS:
                        if(nptr->type == INT_TYPE) {
                            nptr->val.ival = nptr->children[0]->val.ival + nptr->children[1]->val.ival;
                            break;
                        } else {
                            char *first = nptr->children[0]->val.sval;
                            char *second = nptr->children[1]->val.sval;

                            //nptr->val.sval = (char*)malloc(strlen(first));
                            char* cat = (char*)malloc(strlen(first) + 1);
                            
                            strcpy(cat, first);
                            //memcpy(nptr->val.sval, first, strlen(first));
                            strcat(cat, second);
                            //strcat(nptr->val.sval, second);
                            nptr->val.sval = cat;
                            break;
                        } 
                        break;
                    case TOK_BMINUS:
                        nptr->val.ival = nptr->children[0]->val.ival - nptr->children[1]->val.ival;
                        break;
                    case TOK_TIMES:
                        
                        if(nptr->type == INT_TYPE) {
                            nptr->val.ival = nptr->children[0]->val.ival * nptr->children[1]->val.ival;
                        } else {
                            //code to concat n times
                            if(nptr->children[1]->val.ival < 0) {
                                handle_error(ERR_EVAL);
                                break;
                            } else {
                                char *first = nptr->children[0]->val.sval;
                                int second = nptr->children[1]->val.ival;

                                nptr->val.sval = (char*)malloc(strlen(first) * second + 1);
                                strcpy(nptr->val.sval, "");
                                for(int i = 0; i < second; i++) {
                                    strcat(nptr->val.sval, first);
                                }
                                break;
                            }
                        }
                        break;
                    case TOK_DIV:
                    if(nptr->children[1]->val.ival == 0) {
                        handle_error(ERR_EVAL);
                        break;
                    }
                        nptr->val.ival = (int)(nptr->children[0]->val.ival / nptr->children[1]->val.ival);
                        break;
                    case TOK_MOD:
                    if(nptr->children[1]->val.ival == 0) {
                        handle_error(ERR_EVAL);
                        break;
                    }
                        nptr->val.ival = nptr->children[0]->val.ival % nptr->children[1]->val.ival;
                        break;
                    case TOK_AND:
                        nptr->val.bval = nptr->children[0]->val.bval & nptr->children[1]->val.bval;
                        break;
                    case TOK_OR:
                        nptr->val.bval = nptr->children[0]->val.bval || nptr->children[1]->val.bval;
                        break;
                    case TOK_LT:
                        if(nptr->children[0]->type == INT_TYPE) {
                            nptr->val.bval = nptr->children[0]->val.ival < nptr->children[1]->val.ival;
                            break;
                        } else {
                            char *first = nptr->children[0]->val.sval;
                            char *second = nptr->children[1]->val.sval;
                            nptr->val.bval = strcmp(first, second) < 0;
                            break;
                        }
                        
                    case TOK_GT:
                        if(nptr->children[0]->type == INT_TYPE) {
                            nptr->val.bval = nptr->children[0]->val.ival > nptr->children[1]->val.ival;
                            break;
                        } else {
                            char *first = nptr->children[0]->val.sval;
                            char *second = nptr->children[1]->val.sval;
                            nptr->val.bval = strcmp(first, second) > 0;
                            break;
                        }
                    case TOK_EQ:
                        if(nptr->children[0]->type == INT_TYPE) {
                            nptr->val.bval = nptr->children[0]->val.ival == nptr->children[1]->val.ival;
                            break;
                        } else {
                            char *first = nptr->children[0]->val.sval;
                            char *second = nptr->children[1]->val.sval;
                            nptr->val.bval = strcmp(first, second) == 0;
                            break;
                        }
                    case TOK_ASSIGN:;
                        printf("reached assignment safely \n");
                        char* id = nptr->children[0]->val.sval;
                        nptr->type = nptr->children[0]->type;
                        printf("reached assignment safely \n");
                        put(id, nptr->children[1]);
                        break;
                    default:
                        printf("reached default case \n");
                        break;
                }
            }
            if (nptr->tok == TOK_QUESTION) {
                
                eval_node(nptr->children[0]);

                //ternary operator
                if(nptr->children[0]->val.bval) {
                    eval_node(nptr->children[1]);
                    if(nptr->type == INT_TYPE) {
                        nptr->val.ival = nptr->children[1]->val.ival;
                        break;
                    } else if(nptr->type == BOOL_TYPE){
                        nptr->val.bval = nptr->children[1]->val.bval;
                        break;
                    } else {
                        nptr->val.sval = (char*)malloc(strlen(nptr->children[1]->val.sval) + 1);
                        strcpy(nptr->val.sval, nptr->children[1]->val.sval);
                        break;
                    }
                } else {
                    eval_node(nptr->children[2]);
                    if(nptr->type == INT_TYPE) {
                        nptr->val.ival = nptr->children[2]->val.ival;
                        break;
                    } else if(nptr->type == BOOL_TYPE) {
                        nptr->val.bval = nptr->children[2]->val.bval;
                        break;
                    } else {
                        nptr->val.sval = (char*)malloc(strlen(nptr->children[2]->val.sval) + 1);
                        strcpy(nptr->val.sval, nptr->children[2]->val.sval);
                        break;
                    }
                }

            }
            // For reference, the identity (do-nothing) operator has been implemented for you.
            if (nptr->tok == TOK_IDENTITY) {
                eval_node(nptr->children[0]);
                if (nptr->type == STRING_TYPE) {
                    nptr->val.sval = (char *) malloc(strlen(nptr->children[0]->val.sval) + 1);
                    strcpy(nptr->val.sval, nptr->children[0]->val.sval);
                    // Week 2 TODO: You'll need to make a copy of the string.
                } else if(nptr->type == INT_TYPE){
                    nptr->val.ival = nptr->children[0]->val.ival;
                } else {
                    nptr->val.bval = nptr->children[0]->val.bval;
                }
            }
            break;
        case NT_LEAF:
        //what should base case be
            switch(nptr->tok) {
                case TOK_ID:;
                char* id = nptr->val.sval;
                entry_t* entry = get(id);
                free (nptr->val.sval);

                if(entry == NULL) {
                    handle_error(ERR_SYNTAX);
                    break;
                }
                    if(nptr->type == STRING_TYPE) {
                        
                        nptr->val.sval = (char*)malloc(strlen(entry->val.sval) + 1);
                        strcpy(nptr->val.sval, entry->val.sval);
                    } else if(nptr->type == INT_TYPE) {
                        nptr->val.ival = entry->val.ival;
                    } else if(nptr->type == BOOL_TYPE) {
                        nptr->val.bval = entry->val.bval;
                    } else {
                        handle_error(ERR_SYNTAX);
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return;
}

/* eval_root() - set the value of the root node based on the values of children 
 * Parameter: A pointer to a root node, possibly NULL.
 * Return value: None.
 * Side effect: The val dield of the node is updated. 
 */

void eval_root(node_t *nptr) {

    if (nptr == NULL) return;
    // check running status
    if (terminate || ignore_input) return;

    // check for assignment
    if (nptr->type == ID_TYPE) {
        eval_node(nptr->children[1]);
        if (terminate || ignore_input) return;
        
        if (nptr->children[0] == NULL) {
            logging(LOG_ERROR, "failed to find child node");
            return;
        }
        put(nptr->children[0]->val.sval, nptr->children[1]);

        return;
    }

    for (int i = 0; i < 2; ++i) {
        eval_node(nptr->children[i]);
    }
    if (terminate || ignore_input) return;
    
    if (nptr->type == STRING_TYPE) {
        (nptr->val).sval = (char *) malloc(strlen(nptr->children[0]->val.sval) + 1);
        if (! nptr->val.sval) {
            logging(LOG_FATAL, "failed to allocate string");
            return;
        }
        strcpy(nptr->val.sval, nptr->children[0]->val.sval);
    } else {
        nptr->val.ival = nptr->children[0]->val.ival;
    }
    return;
}

/* infer_and_eval() - wrapper for calling infer() and eval() 
 * Parameter: A pointer to a root node.
 * Return value: none.
 * Side effect: The type and val fields of the node are updated. 
 */

void infer_and_eval(node_t *nptr) {
    infer_root(nptr);
    eval_root(nptr);
    return;
}

/* strrev() - helper function to reverse a given string 
 * Parameter: The string to reverse.
 * Return value: The reversed string. The input string is not modified.
 * (STUDENT TODO)
 */

char *strrev(char *str) {
    // Week 2 TODO: Implement copying and reversing the string.
    char *rev = (char*)malloc(strlen(str) + 1);
    strcpy(rev, str);
    for(int i = strlen(str) - 1; i >= 0; i--) {
        rev[strlen(str) - 1 - i] = str[i];
    }
    //printf("%s",rev);
    return rev;
}



/* cleanup() - frees the space allocated to the AST
 * Parameter: The node to free.
 */
void cleanup(node_t *nptr) {
    // Week 2 TODO: Recursively free each node in the AST
    if(nptr == NULL) {
        return;
    }
    for(int i = 0; i < 3; i++) {
        cleanup(nptr->children[i]);
    }
    //free(nptr->val.sval);
    if((nptr->type == STRING_TYPE || nptr->type == ID_TYPE)&& nptr->val.sval != NULL) {
        free(nptr->val.sval);
    }
    free(nptr);
    return;
}
