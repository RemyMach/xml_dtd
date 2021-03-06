typedef struct LinkedListAttribute {
    char* key;
    char* value;
    int present_in_dtd;
    struct LinkedListAttribute* nextAttribute;
}LinkedListAttribute;

typedef struct LinkedListTag {
    int close;
    int present_in_dtd;
    char* name;
    char* text;
    struct LinkedListTag* parentTag;
    struct LinkedListTag* childTags;
    struct LinkedListTag* brotherTags;
    struct LinkedListAttribute* attribute;
}LinkedListTag;

typedef struct LinkedListDtd {
    char* name;
    char operator;
    char* text;
    int present_in_xml;
    struct LinkedListDtd* parentTag;
    struct LinkedListDtd* childTags;
    struct LinkedListDtd* brotherTags;
    struct LinkedListAttributeDtd* attribute;
}LinkedListDtd;

typedef struct LinkedListAttributeDtd {
    char* key;
    char operator;
    int present_in_xml;
    struct LinkedListAttributeDtd* nextAttribute;
}LinkedListAttributeDtd;

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
int present_attribute(LinkedListTag* head);
int presentTagInXml(LinkedListTag* head, char* name_parent_tag, char* name_tag, char operator);
void printTagsDtd(LinkedListDtd* head);
int verifyAllTagsDTD(LinkedListTag* head);

void addLinkedListDtd(char* name, char* text, char operator, char* parent_name, char* brotherAfter, LinkedListDtd* head);
LinkedListDtd* intialisationDtd(char* name);
LinkedListDtd* searchParent(LinkedListDtd* head, char* parent_name);
int matchXmlDtd(LinkedListTag* head, LinkedListDtd* head_dtd);
int verifyAllTagsPresentDtdInXML(LinkedListDtd* head);

void addLinkedListAttributeDtd(char* key, char* parent_tag_dtd, char operator, LinkedListDtd* head_dtd);
void matchXmlDtdAttribute(LinkedListTag* child, LinkedListDtd* child_dtd);
void printAttributeDtd(LinkedListAttributeDtd* firstAttribute);

int verifyAllAttributesTagInDtd(LinkedListAttributeDtd* firstAttribute);
int verifyAllAttributesTagInXml(LinkedListAttribute* firstAttribute);
void freeLinkedListTag(LinkedListTag* head);
void freeLinkedListAttribute(LinkedListAttribute* attribute);