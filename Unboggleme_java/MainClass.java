import java.util.*;

class MainClass{
    public static void main(String args[]){
        Tray something = new Tray();

        int size = Integer.parseInt(args[0]);

        char[][] hello = new char[size][size];

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                hello[i][j] = 'L';
            }
        }

        something.add(hello);

        char[][] goodbye = something.pop();
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                System.out.print(goodbye[i][j]);
            }
            System.out.print('\n');
        }
    }
}
