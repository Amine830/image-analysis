clear


echo -e "\n"
echo "==== Construction de la version graphique ===="
echo -e "\n"


cmake .

echo -e "\n"

echo "==========       Compilation de l'application       ========== " 
echo -e "\n"

cmake --build .

echo -e "\n"
echo "==========   Version CLI construite avec succès !   ========== "
echo -e "\n"

echo "==========        Lancement de l'application        =========="
echo -e "\n"


./QtProject/QtProject

echo -e "\n"
echo "==========        Application fermée        =========="