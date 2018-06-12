package engine;

import java.util.Comparator;
/**
 * Comparador de users por numero de posts feitos.
 * @author Grupo 48
 * @version 12/06/2018
 */
public class ComparadorUsersPorPosts implements Comparator<myUser>
{
    /**
     * Comparador de utilizadores que os ordena por ordem decrescente de número de posts feitos
     * @param u1 Utilizador 1
     * @param u2 Utilizador 2
     * @return Valor >0 se o número de posts do utilizador 1 é menor que a do par 2, <0 se o número de posts do utilizador 2 é menor que a do par 1. Caso as ocorrências sejam iguais, desempata-se comparando os nomes dos utilizadores lexicograficamente
     */
    @Override
    public int compare(myUser u1, myUser u2){ //decrescente
        int valor1=u1.getTotalPosts(), valor2=u2.getTotalPosts();
        if (valor1>valor2)
            return -1;
        if (valor1<valor2)
            return 1;
        return u1.getName().compareTo(u2.getName());
    }
}
