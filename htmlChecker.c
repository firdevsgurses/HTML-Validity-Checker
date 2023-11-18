#include <stdio.h>
#include <stdbool.h>
#include <string.h>


//Firdevs Gurses

bool check_tag(const char *tag) {
    // Regular expression: '^<[a-z]+>$' 
	//We did not use this function in our main call nor in member function call
    int i;
    if (tag[0] == '<' && tag[1] != '/' && tag[strlen(tag) - 1] == '>') {
        for (i = 1; i < strlen(tag) - 1; i++) {
            if (!(tag[i] >= 'a' && tag[i] <= 'z')) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool check_html(const char *html) {
    char stack[100][20]; 
    int top = -1;

    char tag[20];
    int index = 0;
    int i;
    for (i = 0; i < strlen(html); i++) {
        if (html[i] == '<') {
            index = 0;
            i++;
            while (html[i] != '>') {
                tag[index++] = html[i++];
            }
            tag[index] = '\0';

            if (tag[0] != '/') {
                strcpy(stack[++top], tag);
            } else {
                if (top >= 0 && strcmp(stack[top], tag + 1) == 0) {
                    top--;
                } else {
                    printf("error <%s>\n", (top >= 0) ? stack[top] : tag);
                    return false;
                }
            }
        }
    }

    if (top == -1) {
    	printf("correct\n");
        return true;
    } else {
        printf("error <%s>\n", stack[top]);
        return false;
    }
}

int main() {
    char html[1000];
    
    fgets(html, sizeof(html), stdin);
    
    html[strcspn(html, "\n")] = '\0';

    check_html(html); // Output
    
    return 0;
}

