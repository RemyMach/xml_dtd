typedef struct LinkedListAttribute {
    char* key;
    char* value;
    struct LinkedListAttribute* nextAttribute;
}LinkedListAttribute;

typedef struct LinkedListTag {
    int close;
    char* name;
    char* text;
    struct LinkedListTag* parentTag;
    struct LinkedListTag* childTags;
    struct LinkedListTag* brotherTags;
    struct LinkedListAttribute* attribute;
}LinkedListTag;

LinkedListTag* intialisation(char* name);
LinkedListTag* searchCurrentTag(LinkedListTag* head);
int closeTag(char* name, LinkedListTag* currentTag);
void addLinkedListTags(char* name, char* text, int close, LinkedListTag* parent, LinkedListTag* brotherAfter);
void addLinkedListAttribute(char* key, char* value, LinkedListTag* head);
void addTextToLinkedListTag(char* text, LinkedListTag* head);
void addLinkedListBrother(char* name, char* text, LinkedListTag* brotherBefore, LinkedListTag* brotherAfter);
void printAttribute(LinkedListAttribute* firstAttribute);
void printTags(LinkedListTag* head);
int verifyAllTagsClosed(LinkedListTag* head);
int count_depth(LinkedListTag* head);