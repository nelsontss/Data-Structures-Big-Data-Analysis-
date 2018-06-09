package engine;

import li3.TADCommunity;

import java.time.DateTimeException;
import java.time.LocalDate;
import java.util.InputMismatchException;
import java.util.List;
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

    public void startTopMostActive(){
        Scanner sc = new Scanner(System.in);
        String menu; int N;
        menu = viewMenus.getTopMostActiveMenu();
        System.out.print(menu);
        System.out.println("Qual o numero de users que deseja ver no top? ");
        try{
            N = sc.nextInt();
            List<Long> r = estrutura.topMostActive(N);
            System.out.println(r);

        }catch (InputMismatchException e){
            System.out.println(("Nao digitou um numero!"));
        }
    }

    public void startTotalPosts(){
        Scanner sc = new Scanner(System.in);
        String menu; LocalDate begin; LocalDate end;
        menu = viewMenus.getTopMostActiveMenu();

        System.out.println("Qual é a primeira data: ");
        try{
            begin = LocalDate.parse(sc.nextLine());
            System.out.println("Qual é a segunda data: ");
            end = LocalDate.parse(sc.nextLine());
            Pair<Long,Long> p = estrutura.totalPosts(begin,end);
            System.out.println(p);
        }catch (DateTimeException e){
            System.out.println("Datas invalidas!!");
        }
    }

    public void startController(){
        String menu; int op;

        do{
            menu = viewMenus.getMainMenu();
            System.out.print(menu);
            op = lerOpcao();
            switch (op){
                case 0: break;
                case 1: startInfoFromPost();break;
                case 2: startTopMostActive();break;
                case 3: startTotalPosts();break;
                default: System.out.println("Opçao errada!");break;
            }
        } while(op!=0);

    }
}
