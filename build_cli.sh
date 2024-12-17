clear

echo -e "\n"
echo "==========  Construction de la version terminale    ========== "
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


./OpenCVApp

echo -e "\n"
echo "==========        Fin de l'application              =========="

# chmod +x build_terminal.sh build_gui.sh
