package engine;

import com.sun.org.apache.bcel.internal.generic.LUSHR;
import li3.TADCommunity;

import java.time.DateTimeException;
import java.time.LocalDate;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;
import common.Pair;
import org.w3c.dom.ls.LSException;

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
        System.out.println(menu);
        System.out.println("-  Inserir o id do post: ");
        try {
            id = sc.nextLong();
            long before,after;
            before = System.currentTimeMillis();
            Pair<String,String> p = estrutura.infoFromPost(id);
            after = System.currentTimeMillis();
            System.out.println("Titulo: " + p.getFst());
            System.out.println("Nome: " + p.getSnd());
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (InputMismatchException e){
            System.out.print("Id invalido!");
        }


    }

    public void startTopMostActive(){
        Scanner sc = new Scanner(System.in);
        String menu; int N;
        menu = viewMenus.getTopMostActiveMenu();
        System.out.println(menu);
        System.out.println("Qual o numero de users que deseja ver no top? ");
        try{
            N = sc.nextInt();
            long before,after;
            before = System.currentTimeMillis();
            List<Long> r = estrutura.topMostActive(N);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");

        }catch (InputMismatchException e){
            System.out.println(("Nao digitou um numero!"));
        }
    }

    public void startTotalPosts(){
        Scanner sc = new Scanner(System.in);
        String menu; LocalDate begin; LocalDate end;
        menu = viewMenus.getTotalPostsMenu();
        System.out.println(menu);
        System.out.println("Qual é a primeira data: ");
        try{
            begin = LocalDate.parse(sc.nextLine());
            System.out.println("Qual é a segunda data: ");
            end = LocalDate.parse(sc.nextLine());
            long before,after;
            before = System.currentTimeMillis();
            Pair<Long,Long> p = estrutura.totalPosts(begin,end);
            after = System.currentTimeMillis();
            System.out.println(p);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (DateTimeException e){
            System.out.println("Datas invalidas!!");
        }
    }

    public void startQuestionsWithTag(){
        Scanner sc = new Scanner(System.in);
        String menu; LocalDate begin; LocalDate end;
        String tag;
        menu = viewMenus.getQuestionsWithTagMenu();
        System.out.println(menu);
        System.out.println("Qual a tag ?");
        try{
            tag = sc.nextLine();
            System.out.println("Qual é a primeira data: ");
            begin = LocalDate.parse(sc.nextLine());
            System.out.println("Qual é a segunda data: ");
            end = LocalDate.parse(sc.nextLine());
            long before,after;
            before = System.currentTimeMillis();
            List<Long> r = estrutura.questionsWithTag(tag,begin,end);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (DateTimeException e){
            System.out.println("Datas invalidas!!");
        }
    }

    public void startGetUserInfo(){
        Scanner sc = new Scanner(System.in);
        String menu; Long id;
        menu = viewMenus.getUserInfoMenu();
        System.out.println(menu);
        System.out.println("Qual o id ?");
        try {
            id = sc.nextLong();
            long before,after;
            before = System.currentTimeMillis();
            Pair<String,List<Long>> r = estrutura.getUserInfo(id);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (InputMismatchException e){
            System.out.println("Id invalido!!");
        }

    }

    public void startMostVotedAnswers(){
        Scanner sc = new Scanner(System.in);
        String menu; int N;
        LocalDate begin; LocalDate end;
        menu = viewMenus.getMostVotedAnswersMenu();
        System.out.println(menu);
        try {
            System.out.println("Data de inicio: ");
            begin = LocalDate.parse(sc.nextLine());
            System.out.println("Data do fim: ");
            end = LocalDate.parse(sc.nextLine());
            System.out.println("Qual o N?");
            N = sc.nextInt();
            long before,after;
            before = System.currentTimeMillis();
            List<Long> r = estrutura.mostVotedAnswers(N,begin,end);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (Exception e){
            System.out.println("Inputs invalidos!");
        }
    }

    public void startMostAnsweredQuestions(){
        Scanner sc = new Scanner(System.in);
        String menu; int N;
        LocalDate begin; LocalDate end;
        menu = viewMenus.getMostAnsweredQuestionsMenu();
        System.out.println(menu);
        try {
            System.out.println("Data de inicio: ");
            begin = LocalDate.parse(sc.nextLine());
            System.out.println("Data do fim: ");
            end = LocalDate.parse(sc.nextLine());
            System.out.println("Qual o N?");
            N = sc.nextInt();
            long before,after;
            before = System.currentTimeMillis();
            List<Long> r = estrutura.mostAnsweredQuestions(N,begin,end);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (Exception e){
            System.out.println("Inputs invalidos!");
        }
    }

    public void startContainsWord(){
        Scanner sc = new Scanner(System.in);
        String menu; String word;
        int N;
        menu = viewMenus.getContainsWordMenu();
        System.out.println(menu);
        try {
            System.out.println("Qual a palavra: ");
            word = sc.nextLine();
            System.out.println("Qual o N? ");
            N  = sc.nextInt();
            long before,after;
            before = System.currentTimeMillis();
            List<Long> r = estrutura.containsWord(N,word);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (InputMismatchException e){
            System.out.println("Inputs invalidos!");
        }
    }

    public void startBothParticipated(){
        Scanner sc = new Scanner(System.in);
        String menu; Long id1; Long id2;
        int N;
        menu = viewMenus.getBothParticipatedMenu();
        System.out.println(menu);
        try {
            System.out.println("Id do primeiro user: ");
            id1 = sc.nextLong();
            System.out.println("Id do segundo user: ");
            id2 = sc.nextLong();
            System.out.println("Qual o N: ");
            N = sc.nextInt();
            long before,after;
            before = System.currentTimeMillis();
            List<Long> r = estrutura.bothParticipated(N,id1,id2);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (InputMismatchException e){
            System.out.println("Inputs invalidos!");
        }
    }

    public void startBetterAnswer(){
        Scanner sc = new Scanner(System.in);
        String menu; Long id;
        menu = viewMenus.getBetterAnswerMenu();
        System.out.println(menu);
        try {
            System.out.println("Id da pergunta: ");
            id = sc.nextLong();
            long before,after;
            before = System.currentTimeMillis();
            Long r = estrutura.betterAnswer(id);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (InputMismatchException e){
            System.out.println("Inputs invalidos!");
        }
    }

    public void startMostUsedBestRep(){
        Scanner sc = new Scanner(System.in);
        String menu; int N;
        LocalDate begin; LocalDate end;
        menu = viewMenus.getMostUsedBestRepMenu();
        System.out.println(menu);
        try {
            System.out.println("Data de inicio: ");
            begin = LocalDate.parse(sc.nextLine());
            System.out.println("Data do fim: ");
            end = LocalDate.parse(sc.nextLine());
            System.out.println("Qual o N?");
            N = sc.nextInt();
            long before,after;
            before = System.currentTimeMillis();
            List<Long> r = estrutura.mostUsedBestRep(N,begin,end);
            after = System.currentTimeMillis();
            System.out.println(r);
            System.out.println("Tempo -> " + (after-before) + " ms");
        }catch (Exception e){
            System.out.println("Inputs invalidos!");
        }
    }

    public void startController(){
        String menu; int op;
        Scanner sc = new Scanner(System.in);
        do{
            menu = viewMenus.getMainMenu();
            System.out.print(menu);
            op = lerOpcao();
            switch (op){
                case -1: break;
                case 0: System.out.println("Introduza o caminho para os ficheiros: ");estrutura.load(sc.nextLine());break;
                case 1: startInfoFromPost();break;
                case 2: startTopMostActive();break;
                case 3: startTotalPosts();break;
                case 4: startQuestionsWithTag();break;
                case 5: startGetUserInfo();break;
                case 6: startMostVotedAnswers();break;
                case 7: startMostAnsweredQuestions();break;
                case 8: startContainsWord();break;
                case 9: startBothParticipated();break;
                case 10: startBetterAnswer();break;
                case 11: startMostUsedBestRep();break;
                case 12: estrutura.clear();
                default: System.out.println("Opçao errada!");break;
            }
        } while(op!=-1);

    }
}
