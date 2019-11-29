/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package memory;
import java.awt.Color;
import java.awt.GridLayout;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.time.LocalTime;
import static java.time.temporal.ChronoUnit.MINUTES;
import static java.time.temporal.ChronoUnit.SECONDS;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 *
 * @author Laiman
 */
public class GameBoard extends JPanel implements ICardListener{
    private final int ROWS = 2;
    private final int COLUMNS = 2;
    private final int totalCardPairs = (ROWS*COLUMNS)/2;
    private int pairMatched = 0;
    
    private String playerName;
    private LocalTime recordTime;
    private int minutes = 0, seconds = 0;
    
    private Card[][] cells = new Card[ROWS][COLUMNS];
    private ArrayList<Card> cards = new ArrayList<>();
    
    Card firstCard = null;
    Card secondCard = null;
    
    public GameBoard(){
        setLayout(new GridLayout(ROWS, COLUMNS));
        InitializeGameBoard();
    }

    private void InitializeGameBoard() {
        for(int i = 0; i < (ROWS*COLUMNS)/2; i++){
            Card newCard = new Card("Click");
            Card pairNewCard = new Card("Click");
            
            Color newCardColor = newCard.getCardColor();
            pairNewCard.setCardColor(newCardColor);
            
            cards.add(newCard);
            cards.add(pairNewCard);
            
            newCard.addCardClickedListener(this);
            pairNewCard.addCardClickedListener(this);
        }
        Collections.shuffle(cards);
        
        int index = 0;
        for(int row = 0; row < ROWS; row++){
            for(int column = 0; column < COLUMNS; column++){
                cells[row][column] = cards.get(index);
                add(cells[row][column]);
                index = index + 1;
            }
        }
        JOptionPane.showInputDialog("Please enter your name: ", playerName);
        recordTime = LocalTime.now();
    }
    
    @Override
    public void cardClicked(Card theCard) throws IOException {
        if(theCard.isFilped() == false){
            theCard.setBackground(theCard.getCardColor());
            
            if(firstCard != null && secondCard != null){
                firstCard.setBackground(firstCard.getFrontColor());
                secondCard.setBackground(secondCard.getFrontColor());
            }else if(firstCard == null){
                firstCard = theCard;
            }else if(secondCard == null){
                secondCard = theCard;
                if(firstCard.getCardColor().equals(secondCard.getCardColor())){
                    twoCardMatched(firstCard, secondCard);
                    pairMatched++;
                    System.out.println(pairMatched);
                    check4Finish();
                }else{
                    twoCardNotMatch(firstCard, secondCard);
                }
                firstCard = null;
                secondCard = null;
            } 
        }
        else if(theCard.isFilped() == true){
            theCard.setBackground(theCard.getFrontColor());
            firstCard = null;
        }
    }
    
    private void twoCardMatched(Card firstCard, Card secondCard){
        firstCard.setMatched(true);
        secondCard.setMatched(true);
    }

    private void twoCardNotMatch(Card firstCard, Card secondCard) {
        secondCard.setBackground(secondCard.getCardColor());
        
        Timer timer = new Timer();
        timer.schedule(new TimerTask(){
        @Override
            public void run(){
                firstCard.setBackground(firstCard.getFrontColor());
                secondCard.setBackground(secondCard.getFrontColor());
            }
        },1*1000);
    }
    
    private void check4Finish() throws FileNotFoundException, UnsupportedEncodingException, IOException{
        if(pairMatched == totalCardPairs){
            minutes = (int) MINUTES.between(recordTime, LocalTime.now());
            seconds = (int) SECONDS.between(recordTime, LocalTime.now());
            
            PrintWriter fout = new PrintWriter("scores.txt", "UTF-8");
            fout.println(playerName + "/" + minutes + "/" + seconds);
            fout.close();
             
            try (Writer writer = new BufferedWriter(new OutputStreamWriter(
              new FileOutputStream("filename.txt"), "utf-8"))) {
            writer.write(playerName + "/" + minutes + "/" + seconds);
}
            
            JOptionPane.showMessageDialog(this, "You win!\nTime:   " + minutes + ":" + seconds);
        }
    }
 
    void shouSolution() {
        for(int i = 0; i < ROWS; i++){
            for(int j = 0; j < COLUMNS; j++){
                Card card = cells[i][j];
                card.setBackground(card.getCardColor());
                card.setMatched(true);
            }
        }
    }
}
