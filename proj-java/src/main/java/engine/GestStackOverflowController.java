package engine;

import li3.TADCommunity;

import java.util.InputMismatchException;
import java.util.Scanner;
import common.Pair;

public class GestStackOverflowController {
    private TADCommunity  estrutura;
    private GestStackOverflowView viewMenus;

    public void setView(GestStackOverflowView m) {
        viewMenus = m;
    }

    public void setModel(TADCommunity e){
        estrutura = e;
    }


    public int lerOpcao(){
        Scanner sc = new Scanner(System.in);
        int r = 0;
        try {
                r = sc.nextInt();
            }catch (InputMismatchException e){
                System.out.println("Nao introduzio um numero!");
                lerOpcao();
            }


        return r;
    }

    public void startInfoFromPost(){
        Scanner sc = new Scanner(System.in);
        String menu; long id;
        menu = viewMenus.getInfoFromPostMenu();
        System.out.print(menu);
        System.out.print("\n-  Inserir o id do post: ");
        try {
            id = sc.nextLong();
            Pair<String,String> p = estrutura.infoFromPost(id);
            System.out.print("\nTitulo: " + p.getFst());
            System.out.print("\nNome: " + p.getSnd());
        }catch (InputMismatchException e){
            System.out.print("\n id invalido!");
        }


    }

    public void startController(){
        String menu; int op;

        do{
            menu = viewMenus.getMainMenu();
            System.out.print(menu);
            op = lerOpcao();
            switch (op){
                case 1: startInfoFromPost();break;
                default: System.out.println("Opçao errada!");break;
            }
        } while(op!=0);

    }
}
