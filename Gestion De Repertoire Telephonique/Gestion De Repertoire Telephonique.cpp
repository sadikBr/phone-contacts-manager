#include <iostream>
#include <vector>

using namespace std;

class Contact {
private:
	string firstName;
	string lastName;
	string number;
	string email;
	string adress;

public:
	Contact(string fn, string num, string ln = "", string em = "", string adr = "") {
		firstName = fn;
		lastName = ln;
		number = num;
		email = em;
		adress = adr;
	}

	string getFirstName() {
		return firstName;
	}

	string getNumber() {
		return number;
	}

	void showContact() {
		cout << getFirstName() << ": " << getNumber() << endl;
	}
};

class Group {
private:
	string groupName;
	vector<Contact> contacts;

public:
	Group(string gn) {
		groupName = gn;
	}

	string getGroupName() {
		return groupName;
	}

	void addContact(Contact contact) {
		contacts.push_back(contact);
	}

	void showGroup() {
		cout << getGroupName() << ": " << endl;
		for (int i = 0; i < contacts.size(); i++) {
			contacts[i].showContact();
		}
	}
};

class Repertory {
private:
	string repertoryName;
	vector<Contact> contacts;
	vector<Group> groups;

public:
	Repertory(string rn) {
		repertoryName = rn;
	}

	vector<Contact> getContacts() {
		return contacts;
	}

	vector<Group> getGroups() {
		return groups;
	}

	void setContacts(vector<Contact> elements) {
		contacts = elements;
	}

	void setGroups(vector<Group> elements) {
		groups = elements;
	}

	string getRepertoryName() {
		return repertoryName;
	}

	void show() {
		cout << ' ' << getRepertoryName() << endl;
	}

	void showAllContacts() {
		for (int i = 0; i < getContacts().size(); i++) {
			contacts[i].showContact();
		}
	}

	void showAllGroups() {
		for (int i = 0; i < getGroups().size(); i++) {
			getGroups()[i].showGroup();
		}
	}

	void addContactToRepertory(Contact contact) {
		vector<Contact> allContacts = getContacts();
		allContacts.push_back(contact);
		setContacts(allContacts);
	}

	void removeContactFromRepertory(Contact contact) {
		vector<Contact> existingContacts;
		vector<Contact> allContacts = getContacts();
		for (int i = 0; i < allContacts.size(); i++) {
			if (contact.getNumber() == allContacts[i].getNumber()) {
				continue;
			}
			else {
				existingContacts.push_back(allContacts[i]);
			}
		}
		setContacts(existingContacts);
	}

	Contact findContactByNumber(string num) {
		vector<Contact> allContacts = getContacts();
		for (int i = 0; i < allContacts.size(); i++) {
			if (num == allContacts[i].getNumber()) {
				return allContacts[i];
			}
		}
	}

	Contact findContactByName(string fn) {
		vector<Contact> allContacts = getContacts();
		for (int i = 0; i < allContacts.size(); i++) {
			if (fn == allContacts[i].getFirstName()) {
				return allContacts[i];
			}
		}
	}

	void createGroup(Group grp) {
		vector<Group> allGroups = getGroups();
		allGroups.push_back(grp);
		setGroups(allGroups);
	}

	void deleteGroup(string gn) {
		vector<Group> existingGroups;
		vector<Group> allGroups = getGroups();
		for (int i = 0; i < allGroups.size(); i++) {
			if (gn == allGroups[i].getGroupName()) {
				continue;
			}
			else {
				existingGroups.push_back(allGroups[i]);
			}
		}
		setGroups(existingGroups);
	}
};

int main() {
	char input;
	char backToMain;
	vector<Repertory> repertories;

	do {
		cout << "-----------------------------------------------------------------" << endl;

		cout << "1:-------------| Afficher les repertoires  |---------------------" << endl;
		cout << "2:-------------|Creer un nouveau repertoire|---------------------" << endl;
		cout << "3:-------------|  Supprimer un repertoire  |---------------------" << endl;

		cout << "---------------|      Faites un choix      |---------------------" << endl;
		cout << "-----------------------------------------------------------------" << endl;

		cin >> input;

		switch (input) {
		case '1': {
			int repNum;
			for (int i = 0; i < repertories.size(); i++) {
				cout << i + 1 << "- ";
				repertories[i].show();
			}

			if (repertories.size() != 0) {
				cout << "Choisir un repertoire: ";
				cin >> repNum;
				Repertory selectedRepertory = repertories[repNum - 1];

				char input;
				char confirm;

				do {
					cout << "---------------|" << "            " << selectedRepertory.getRepertoryName() << "           " << "|---------------------" << endl;

					cout << "1:-------------|   Afficher les contacts   |---------------------" << endl;
					cout << "2:-------------|    Afficher les groups    |---------------------" << endl;
					cout << "3:-------------|   Creer un nouveau group  |---------------------" << endl;
					cout << "4:-------------|     Supprimer un group    |---------------------" << endl;
					cout << "5:-------------|  Creer un nouveau contact |---------------------" << endl;
					cout << "6:-------------|    Supprimer un contact   |---------------------" << endl;
					cout << "q:-------------|       Menu Principal      |---------------------" << endl;

					cout << "---------------|      Faites un choix      |---------------------" << endl;
					cout << "-----------------------------------------------------------------" << endl;

					cin >> input;

					switch (input) {
					case '1': {
						if (selectedRepertory.getContacts().size() == 0) {
							cout << "Vide ..." << endl;
						}
						else {
							selectedRepertory.showAllContacts();
						}
						break;
					}
					case '2': {
						if (selectedRepertory.getGroups().size() == 0) {
							cout << "Vide ..." << endl;
						}
						else {
							selectedRepertory.showAllGroups();
						}
						break;
					}
					case '3': {
						string gn;
						char filterChoice;
						string contactInfo;
						cout << "Donner le nom du group (sans espace): ";
						cin >> gn;
						Group newGroup = Group(gn);
						cout << endl << "------ Choisir les contacts a ajouter au group ------";

						do {
							cout << endl << "Taper 1 pour choisir les contacts par nom et 2 pour les choisir par numero et (q) pour finir l'insertion': ";
							cin >> filterChoice;

							switch (filterChoice) {
							case '1': {
								cout << "Entrer le nom du contact a ajouter: ";
								cin >> contactInfo;
								bool found = false;
								for (int i = 0; i < selectedRepertory.getContacts().size(); i++) {
									Contact contact = selectedRepertory.getContacts()[i];
									if (contact.getFirstName() == contactInfo) {
										found = true;
										newGroup.addContact(contact);
										break;
									}
								}

								if (found == false) {
									cout << "Contact Not Found!";
								}
								break;
							}

							case '2': {
								cout << "Entrer le numero du contact a ajouter: ";
								cin >> contactInfo;
								bool found = false;
								for (int i = 0; i < selectedRepertory.getContacts().size(); i++) {
									Contact contact = selectedRepertory.getContacts()[i];
									if (contact.getNumber() == contactInfo) {
										found = true;
										newGroup.addContact(contact);
										break;
									}
								}

								if (found == false) {
									cout << "Contact Not Found!";
								}
								break;
							}

							case 'q': {
								break;
							}
							}
						} while (filterChoice != 'q');
						selectedRepertory.createGroup(newGroup);
						break;
					}
					case '4': {
						string gn;
						cout << "Entrer le nom du group a supprimer: ";
						cin >> gn;
						selectedRepertory.deleteGroup(gn);
						break;
					}
					case '5': {
						string fn, ln, num, em, adr;
						cout << "Entrer le Prenom (Obligatoire): ";
						cin >> fn;
						cout << endl << "Entrer le Nom (@ pour ignorer): ";
						cin >> ln;
						cout << endl << "Entrer le Numero (Obligatoire): ";
						cin >> num;
						cout << endl << "Entrer l'email (@ pour ignorer): ";
						cin >> em;
						cout << endl << "Entrer l'adresse (@ pour ignorer): ";
						cin >> adr;
						cout << endl;

						if (ln == "@") ln = "";
						if (em == "@") ln = "";
						if (adr == "@") ln = "";

						Contact userContact = Contact(fn, num, ln, em, adr);
						selectedRepertory.addContactToRepertory(userContact);

						cout << fn << " added to " << selectedRepertory.getRepertoryName() << endl;
						break;
					}
					case '6': {
						char filterChoice;
						string contactInfo;
						cout << endl << "Taper 1 pour suprimer un contact par nom et 2 pour le suprimer par numero: ";
						cin >> filterChoice;

						switch (filterChoice) {
						case '1': {
							cout << "Entrer le nom du contact a suprimer: ";
							cin >> contactInfo;
							vector<Contact> allContacts = selectedRepertory.getContacts();
							for (int i = 0; i < allContacts.size(); i++) {
								Contact contact = allContacts[i];
								if (contact.getFirstName() == contactInfo) {
									selectedRepertory.removeContactFromRepertory(contact);
								}
							}
							break;
						}

						case '2': {
							cout << "Entrer le numero du contact a suprimer: ";
							cin >> contactInfo;
							vector<Contact> allContacts = selectedRepertory.getContacts();
							for (int i = 0; i < allContacts.size(); i++) {
								Contact contact = allContacts[i];
								if (contact.getNumber() == contactInfo) {
									selectedRepertory.removeContactFromRepertory(contact);
								}
							}
							break;
						}
						}
						break;
					}
					default: {
						break;
					}
					}
					cout << "Entrer y ou Y pour continuer | n ou N pour retourner au menu principal: ";
					cin >> confirm;
				} while (confirm == 'y' || confirm == 'Y');
			}
			else {
				cout << "Vide ...." << endl;
			}
			break;
		}
		case '2': {
			string rn;
			cout << "Entrer le nom du repertoire a creer (sans espace): ";
			cin >> rn;
			Repertory newRepertory = Repertory(rn);

			repertories.push_back(newRepertory);
			break;
		}
		case '3': {
			string repName;
			cout << "Entrer le nom du repertoire a suprimer: ";
			cin >> repName;
			bool found = false;
			vector<Repertory> existingRepertories;

			for (int i = 0; i < repertories.size(); i++) {
				Repertory rep = repertories[i];
				if (repName == rep.getRepertoryName()) {
					found = true;
					continue;
				}
				else {
					existingRepertories.push_back(rep);
				}
			}
			if (found == false) {
				cout << "Repertory Not Found!" << endl;
			}
			repertories = existingRepertories;
			break;
		}
		default:
			break;
		}
		cout << "Entrer y ou Y pour retourner au menu principal: ";
		cin >> backToMain;
	} while (backToMain == 'y' || backToMain == 'Y');

	return 0;
}
