# MENU TEST

## not_valid

### **1**
- pas valide car la balise root ne se ferme pas

### **2**
- pas valide car une seule balise xml et pas de balise root

### **3**
- fichier vide

### **4**
- la balise jean se ferme après la fermeture d'une de ses balises parent

### **5**
- la valeur de l'attribut contient des valeur qui ne faut pas et ne permet pas de fermer la balise root

### **6**
- il manque un = au dernier attribut, mauvaise typo

### **7**
- deux noms d'attributs pour une même balise sont les mêmes

### **8**
- mauvaise typo pour les noms d'attributs

### **9**
- une balise qui n'est pas fermé

### **10**
- un commentaire avant la balise xml rend le fichier xml non valide


## valid

### **1**
- fichier avec attributs multiples et profondeur supérieur à 1
- valide pour la partie 3 et 4

### **2**
- fichier avec profondeur de 1 et pas d'attributs
- valide pour la partie 1 , 2, 3 et 4

### **3**
- fichier avec profondeur de plus de un, retour chariot multiple, espace multiple dans le texte et  dans les balises
- valide pour la partie 3 et 4

### **4**
- fichier avec profondeur de plus de un, attributs, retour chariot multiple, espace multiple dans le texte et  dans les balises
- valide pour la partie 3 et 4

### **5**
- fichier avec profondeur de plus de un, attributs, balises présentes plusieurs fois.
- valide pour la partie 3 et 4

### **6**
- fichier avec profondeur de plus de un, attributs, balises présentes plusieurs fois et espace et retour chariot à la fin du fichier et au début.
- valide pour la partie 3 et 4

### **7**
- fichier avec profondeur de plus de un, attributs, tests de carractères spéciaux
- valide pour la partie 3 et 4

### **8**
- fichier avec profondeur de plus de un, attributs, tests de carractères spéciaux, balise unique etc...
- valide pour la partie 3 et 4

### **9**
- fichier avec profondeur de plus de un, attributs, tests de carractères spéciaux, balise unique et beaucoup de carractères.
- valide pour la partie 3 et 4

### **10**
- fichier avec profondeur un, attributs, balise unique et commenatires
- valide pour la partie 2, 3 et 4

### **11**
- fichier avec profondeur un, grande balise commentaire
- valide pour la partie 1, 2, 3 et 4

### **12**
- fichier avec profondeur de un, balise commentaire et text
- valide pour la partie 1, 2, 3 et 4