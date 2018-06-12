package engine;

import java.time.LocalDate;
/**
 * Classe que implementa uma resposta
 *
 * @author Grupo 48
 * @version 12/6/2018
 */
public class Resposta extends MyPost
{
    // Variáveis de instancia da classe resposta
    private String parentID;
    private int comments;
    private int score;
    private double pont;
    
    /**
     * Construtor vazio da classe resposta
     */
    public Resposta()
    {
        // initialise instance variables
        super();
        this.parentID="";
        this.comments=0;
        this.score=0;
        this.pont=0;
    }

    /**
     * Construtor parametrizado da classe resposta
     * @param pID ID da pergunta a que a resposta pertence
     * @param comm Número de comentários da resposta
     * @param score Número de Up Votes - Down Votes
     * @param id ID da resposta
     * @param ownerUser ID do proprietário da resposta
     * @param data Data da resposta
     */
    public Resposta(String pID, int comm, int score, String id, String ownerUser, LocalDate data)
    {
        // initialise instance variables
        super(id,ownerUser, data);
        this.parentID=pID;
        this.comments=comm;
        this.score=score;
        this.pont=0.0;    
    }

    /**
     * Construtor de cópia da classe resposta
     * @param r1 Resposta que se pretende duplicar
     */
    public Resposta(Resposta r1)
    {
        // initialise instance variables
        super(r1);
        this.parentID=r1.getParentID();
        this.comments=r1.getNComments();
        this.score=r1.getScore();
        this.pont=r1.getPont();
    }
    
    //gets & sets

    /**
     * Função que devolve o ID da pergunta a que a resposta pertence
     * @return ID da pergunta a que a resposta pertence
     */
    public String getParentID(){
        return this.parentID;
    }

    /**
     * Função que devolve o número de comentários da resposta
     * @return Número de comentários da resposta
     */
    public int getNComments(){
        return this.comments;
    }

    /**
     * Função que devolve número de Up Votes-Down Votes
     * @return Número de Up Votes-Down Votes
     */
    public int getScore(){
        return this.score;
    }

    /**
     * Função que devolve a pontuação da resposta
     * @return Pontuação da resposta
     */
    public double getPont(){
        return this.pont;
    }

    /**
     * Função que define o ID da pergunta a que a resposta pertence
     * @param pID ID da pergunta a que a resposta pertence
     */
    public void setParentID(String pID){
        this.parentID=pID;
    }

    /**
     * Função que define o número de comentários da resposta
     * @param comm Número de comentários da resposta
     */
    public void setNComments(int comm){
        this.comments=comm;
    }

    /**
     * Função que define o número de Up Votes-Down Votes
     * @param score Número de Up Votes-Down Votes
     */
    public void setScore(int score){
        this.score=score;
    }

    /**
     * Função que define a pontuação da resposta
     * @param pont Pontuação da resposta
     */
    public void setPont(double pont){
        this.pont=pont;
    }

    /**
     * Função que faz o cálculo da pontuação da resposta
     * @param reputation Reputação do proprietário da resposta
     * @return Pontuação da resposta
     */
    public double calc_post_pont (int reputation){
        double r = this.score*0.65 + reputation*0.25 + this.comments*0.1;
        this.pont = r;
        return r;
    }

    /**
     * Função que averigua se uma resposta e um objeto são iguais
     * @param o Objeto a comparar
     * @return True se forem iguais, false se não forem
     */
    public boolean equals(Object o){
        if(this==o) return true;
        if(o==null && this.getClass()!=o.getClass()) return false;
        
        Resposta r= (Resposta) o;
        return(super.equals(o) && this.getParentID().equals(r.getParentID()) && this.getNComments() == r.getNComments()
        && this.getScore() == r.getScore() && this.getPont() == r.getPont());
    }

    /**
     * Função que transforma uma resposta numa String
     * @return String representativa da resposta
     */
    public String toString(){
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append(" nId da pergunta: ");sb.append(this.parentID);
        sb.append("\nNumero de comentarios: ");sb.append(this.comments);
        sb.append("\nScore: ");sb.append(this.score);
        sb.append("\nPontuaçao: ");sb.append(this.pont);
        return sb.toString();
    }

    /**
     * Função que duplica uma resposta
     * @return Resposta duplicada
     */
    public Resposta clone(){
        return new Resposta(this);
    }
}
