FILE* openFile(char* filePath);
void closeFile(FILE* pt_fichier);
int readBaliseXml(char char_file);
char* concatenateCharInString(char* s, char char_file);
int verifyBaliseXML(char* s);
int regexSpaceBackSlachPlus(char* s,int* i);
void regexSpaceBackSlachPlusProofNotRequired(char* s,int* i, int* proof);
void regexSpaceBackSlachMultiple(char* s,int* i);
int regexRequiredBloc(char* s,int* i, char* bloc);
int verifyOnlySpaceOrBackSlach(char* s);
int regexSpaceBackSlachOnly(char* s,int* i);
int verifTagSynthaxe(char* s);
int verifTagCloseSynthaxe(char* s);
int verifyTextSynthaxe(char* s);
int regexBracketPlus(char* s,int* i);
int regexBracketOne(char* s, int* i);
int regexBracketNumberSpecialMultiple(char *s,int* i, char delimiter1, char delimiter2, char delimiter3, char* special_characters);
char* getCarracTagXml(FILE* pt_fichier);
char* getCarracTag(FILE* pt_fichier);
char* getCarracBeforeDelimiter(FILE* pt_fichier, char delimiter,int verifyCarrac);
char* getCarracTagClose(FILE* pt_fichier);
char* getCarracText(FILE* pt_fichier);
int readAllOtherTags(FILE* pt_fichier, LinkedListTag* head);

int extractTagNameAndAttrbute_ADD(char* s, LinkedListTag* head);
char* extractTagName(char* s, int* i);
int extractTagAttribute_ADD(char* s,int* i, LinkedListTag* head);
int verifyLinkedListAttribute(char* attribute_key, LinkedListTag* head);
char* extractTagAttributeKey(char* s, int* i);
char* extractTagAttributeValue(char* s, int* i);

void extractText_ADD(char* s, LinkedListTag* head);

int extractTagName_close(char* s, LinkedListTag* head);
int validateRead(LinkedListTag* head, char* pathFile);

int validateDepthSpecify(LinkedListTag* head, int depth_max);
int validateNoAttributes(LinkedListTag* head);
int validateFirstPart(LinkedListTag* head, char* pathFile);
int validateSecondPart(LinkedListTag* head, char* pathFile);
int getCarracComment(FILE* pt_fichier,char char_file);
int determinateUniqueTag(int valid,char* s,int* i);
void freeChar(char* s);